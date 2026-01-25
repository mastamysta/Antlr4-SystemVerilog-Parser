#pragma once

#include <iostream>

#include <antlr4-runtime.h>

#include "SVLexer.h"
#include "SVParser.h"
#include "SVVisitor.h"

#include "Signal.hpp"

static constexpr Signal::SignalWidth PLACEHOLDER_ONE_BIT = 1;

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
        declare_signal<Signal::WIRE>(context->name->getText(), PLACEHOLDER_ONE_BIT);

        return {};
    }

    std::any visitOutreg(SVParser::OutregContext *context) override
    {
        declare_signal<Signal::REG>(context->name->getText(), PLACEHOLDER_ONE_BIT);

        return {};
    }

    std::any visitModule_body(SVParser::Module_bodyContext *context) override
    {
        for (const auto& block: context->module_block())
            block->accept(this);

        return {};
    }

    std::any visitProc(SVParser::ProcContext *context) override
    {
        return {};
    }

    std::any visitReg_decl(SVParser::Reg_declContext *context) override
    {
        declare_signal<Signal::REG>(context->name->getText(), 1);

        return {};
    }

    std::any visitWire_decl(SVParser::Wire_declContext *context) override
    {
        declare_signal<Signal::WIRE>(context->name->getText(), 1);

        return {};
    }

    std::any visitSync_proc(SVParser::Sync_procContext *context) override
    {
        context->signal_trans()->accept(this);

        for (const auto block_body: context->block_body())
            block_body->accept(this);

        return {};
    }

    std::any visitSignal_trans(SVParser::Signal_transContext *context) override
    {
        // This really just needs to specify what event to listen to for any
        // following assignments.
        return {};
    }

    std::any visitIf(SVParser::IfContext *context)
    {
        // Do something with the condition expression.
        auto condition_signal_name = context->expr()->accept(this);

        for (const auto block_body: context->block_body())
            block_body->accept(this);

        return {};
    }

    std::any visitStmt(SVParser::StmtContext *context)
    {
        return {};
    }

    std::any visitBlock_ops(SVParser::Block_opsContext *context) override
    {
        return {};
    }

    // std::any visitDiv(SVParser::DivContext *context) override
    // {
    //     return {};
    // }

    // std::any visitAdd(SVParser::AddContext *context) override
    // {
    //     return {};
    // }

    // std::any visitSub(SVParser::SubContext *context) override
    // {
    //     return {};
    // }

    // std::any visitBrack(SVParser::BrackContext *context) override
    // {
    //     return {};
    // }

    // std::any visitMul(SVParser::MulContext *context) override
    // {
    //     return {};
    // }

    std::any visitLit(SVParser::LitContext *context) override
    {
        auto literal_text = context->INT()->getSymbol()->getText();

        if (!signals.contains(literal_text))
        {
            auto id = declare_signal<Signal::WIRE>(literal_text, PLACEHOLDER_ONE_BIT);
            auto literal_value = std::stoul(literal_text);

            assign_signal(literal_text, [literal_value](Signal::SignalMap){ 
                return literal_value; 
            });
        }

        return {literal_text};
    }

    std::any visitVar(SVParser::VarContext *context) override
    {
        auto signal_name = context->name->getText();

        if (!signals.contains(signal_name))
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

        if (!signals.contains(not_signal_name))
        {
            auto id = declare_signal<Signal::WIRE>(not_signal_name, PLACEHOLDER_ONE_BIT);

            assign_signal(not_signal_name, [inner_signal_name](Signal::SignalMap signals){ 
                return !(signals[inner_signal_name].m_eval(signals)); 
            });
        }

        return not_signal_name;
    }

    std::any visitBitwise_not(SVParser::Bitwise_notContext *context) override
    {
        auto inner_signal_name = std::any_cast<std::string>(context->expr()->accept(this));
        auto bnot_signal_name = "bitwise_not_" + inner_signal_name;

        if (!signals.contains(bnot_signal_name))
        {
            auto id = declare_signal<Signal::WIRE>(bnot_signal_name, PLACEHOLDER_ONE_BIT);

            assign_signal(bnot_signal_name, [inner_signal_name](Signal::SignalMap signals){ 
                return ~(signals[inner_signal_name].m_eval(signals)); 
            });
        }

        return bnot_signal_name;
    }

    std::any visitStatement(SVParser::StatementContext *context) override
    {
        return {};
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

private:
    Signal::SignalMap signals;

    Signal::SignalID next_signal_id = 0;

    template <Signal::SignalType Type>
    Signal::SignalID declare_signal(const std::string& name, const std::size_t width)
    {
        if constexpr (DebugMessages)
            std::cout << "Instance of signal " << name << std::endl;

        signals[name] = {next_signal_id, {}, Type};

        return next_signal_id++;
    }

    void assign_signal(const std::string& name, Signal::SignalEvaluationFunction eval)
    {
        signals[name].m_eval = eval;
    }
};

using ModuleVisitorDebug = ModuleVisitorImpl<true>;
using ModuleVisitor = ModuleVisitorImpl<false>;
