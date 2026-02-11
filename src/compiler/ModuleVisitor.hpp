#pragma once

#include <iostream>
#include <vector>

#include <antlr4-runtime.h>

#include "SVLexer.h"
#include "SVParser.h"
#include "SVVisitor.h"

#include "Signal.hpp"

namespace simulator
{

static constexpr SignalWidth PLACEHOLDER_ONE_BIT = 1;

template <bool DebugMessages>
class ModuleVisitorImpl : public SVVisitor
{
public:

    std::any visitModule(SVParser::ModuleContext *context) override
    {
        context->module_header()->accept(this);
        context->module_body()->accept(this);
        return {};
    }

    std::any visitModule_header(SVParser::Module_headerContext *context) override
    {
        context->ports()->accept(this);
        return {};
    }

    std::any visitPorts(SVParser::PortsContext *context) override
    {
        for (const auto& p: context->port())
            p->accept(this);

        return {};
    }

    std::any visitInwire(SVParser::InwireContext *context) override
    {
        declare_signal<SignalType::WIRE>(context->name->getText(), PLACEHOLDER_ONE_BIT);

        return {};
    }

    std::any visitOutreg(SVParser::OutregContext *context) override
    {
        declare_signal<SignalType::REG>(context->name->getText(), PLACEHOLDER_ONE_BIT);

        return {};
    }

    std::any visitModule_body(SVParser::Module_bodyContext *context) override
    {
        for (const auto& block: context->module_block())
            block->accept(this);

        return {};
    }

    std::any visitReg_decl(SVParser::Reg_declContext *context) override
    {
        declare_signal<SignalType::REG>(context->name->getText(), 1);

        return {};
    }

    std::any visitWire_decl(SVParser::Wire_declContext *context) override
    {
        declare_signal<SignalType::WIRE>(context->name->getText(), 1);

        return {};
    }

    std::any visitSync_proc(SVParser::Sync_procContext *context) override
    {
        context->signal_trans()->accept(this);

        for (const auto block_body: context->block_body())
            block_body->accept(this);

        return {};
    }

    std::any visitInitial_proc(SVParser::Initial_procContext *context) override
    {
        // TODO: Convert this visitor into an AST generator. Then we can visit upon the AST
        // to generate structures for initial blocks *separately* to signal validation and
        // sensitivity construction.
        return {};
    }

    std::any visitSignal_trans(SVParser::Signal_transContext *context) override
    {
        // This really just needs to specify what event to listen to for any
        // following assignments.
        m_sensitivity_context = context->name->getText();
        return {};
    }

    std::any visitIf(SVParser::IfContext *context)
    {
        auto condition_signal_name = std::any_cast<std::string>(context->expr()->accept(this));
        m_condition_context.push_back(condition_signal_name);

        for (const auto block_body: context->block_body())
            block_body->accept(this);

        m_condition_context.pop_back();
        return {};
    }
 
    std::any visitBlock_ass(SVParser::Block_assContext *context) override
    {
        const auto assignee_name = std::any_cast<std::string>(context->left->getText());
        const auto assignment_signal_name = std::any_cast<std::string>(context->right->accept(this));

        const auto old_next_val_func = m_signals[assignee_name].m_next_value;
        const auto current_condition_context = m_condition_context;
        
        m_signals[assignee_name].m_next_value = [assignee_name, old_next_val_func, current_condition_context, assignment_signal_name](SignalMap signal_map){
            if (std::all_of(current_condition_context.cbegin(), current_condition_context.cend(), [assignee_name, &signal_map](std::string condition){
                return signal_map[condition].m_eval(signal_map) == 1;
            }))
            {
                // If all conditions are met, evaluate the assigned expression as the new value for the signal.
                std::cout << assignee_name << " is " << assignment_signal_name << std::endl;
                return signal_map[assignment_signal_name].m_eval(signal_map);
            }
            else
            {
                // ...otherwise, just evaluate the pre-existing eval function.
                std::cout << "Calling off condition " << std::endl;
                return old_next_val_func(signal_map);
            }
        };

        m_signals[m_sensitivity_context].m_dependent_signals.insert(assignee_name);

        return {};
    }

    std::any visitNon_block_ass(SVParser::Non_block_assContext *context) override
    {
        return {};
    }

    std::any visitBrack(SVParser::BrackContext *context) override
    {
        return {};
    }

    std::any visitDiv(SVParser::DivContext *context) override
    {
        return {};
    }

    std::any visitAdd(SVParser::AddContext *context) override
    {
        return {};
    }

    std::any visitSub(SVParser::SubContext *context) override
    {
        return {};
    }

    std::any visitMul(SVParser::MulContext *context) override
    {
        return {};
    }

    std::any visitLit(SVParser::LitContext *context) override
    {
        auto literal_text = context->INT()->getSymbol()->getText();

        if (!m_signals.contains(literal_text))
        {
            auto id = declare_signal<SignalType::WIRE>(literal_text, PLACEHOLDER_ONE_BIT);
            auto literal_value = std::stoul(literal_text);

            assign_signal(literal_text, [literal_value](SignalMap){ 
                return literal_value; 
            });
        }

        return {literal_text};
    }

    std::any visitVar(SVParser::VarContext *context) override
    {
        auto signal_name = context->name->getText();

        if (!m_signals.contains(signal_name))
        {
            std::cout << "ERROR: Reference to undefined signal " << signal_name << std::endl;
            return {};
        }

        return signal_name;
    }

    std::any visitNot(SVParser::NotContext *context) override
    {
        auto inner_signal_name = std::any_cast<std::string>(context->expr()->accept(this));
        auto not_signal_name = "not_" + inner_signal_name;

        if (!m_signals.contains(not_signal_name))
        {
            auto id = declare_signal<SignalType::WIRE>(not_signal_name, PLACEHOLDER_ONE_BIT);

            assign_signal(not_signal_name, [inner_signal_name](SignalMap m_signals){ 
                return !(m_signals[inner_signal_name].m_eval(m_signals)); 
            });
        }

        return not_signal_name;
    }

    std::any visitBitwise_not(SVParser::Bitwise_notContext *context) override
    {
        auto inner_signal_name = std::any_cast<std::string>(context->expr()->accept(this));
        auto bnot_signal_name = "bitwise_not_" + inner_signal_name;

        if (!m_signals.contains(bnot_signal_name))
        {
            auto id = declare_signal<SignalType::WIRE>(bnot_signal_name, PLACEHOLDER_ONE_BIT);

            // TODO: For now we mask the upper bits of the signal, because we only accept single-bit
            // signals.
            assign_signal(bnot_signal_name, [inner_signal_name](SignalMap m_signals){
                return ~(m_signals[inner_signal_name].m_eval(m_signals)) & 0x1;
            });
        }

        return bnot_signal_name;
    }

    void visitDesign()
    {
        std::cout << "Reading in design." << std::endl;
        
        auto stream = std::ifstream{};
        stream.open("/home/bread/sim/design.sv");
        
        auto input = antlr4::ANTLRInputStream{stream};
        auto lexer = SVLexer{&input};
        auto tokens = antlr4::CommonTokenStream{&lexer};
        auto parser = SVParser{&tokens};    
        auto tree = parser.module();

        visitModule(tree);
    }

    const auto& get_signals() const
    {
        return m_signals;
    }

private:
    SignalMap m_signals;
    SignalID m_next_signal_id = 0;

    std::vector<std::string> m_condition_context;
    std::string m_sensitivity_context;

    template <SignalType Type>
    SignalID declare_signal(const std::string& name, const std::size_t width)
    {
        if constexpr (DebugMessages)
            std::cout << "Instance of signal " << name << std::endl;

        m_signals[name] = {m_next_signal_id, {}, Type};

        return m_next_signal_id++;
    }

    void assign_signal(const std::string& name, SignalEvaluationFunction eval)
    {
        m_signals[name].m_eval = eval;
    }
};

using ModuleVisitorDebug = ModuleVisitorImpl<true>;
using ModuleVisitor = ModuleVisitorImpl<false>;

}