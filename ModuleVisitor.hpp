#pragma once

#include <iostream>

#include <antlr4-runtime.h>

#include "SVLexer.h"
#include "SVParser.h"
#include "SVVisitor.h"

#include "Register.hpp"


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
        declare_wire(context->name->getText(), 1);

        return {};
    }

    std::any visitOutreg(SVParser::OutregContext *context) override
    {
        declare_register(context->name->getText(), 1);

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
        declare_register(context->name->getText(), 1);

        return {};
    }

    std::any visitWire_decl(SVParser::Wire_declContext *context) override
    {
        declare_wire(context->name->getText(), 1);

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
        return {};
    }

    std::any visitIf(SVParser::IfContext *context)
    {
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

    std::any visitBrack(SVParser::BrackContext *context) override
    {
        return {};
    }

    std::any visitMul(SVParser::MulContext *context) override
    {
        return {};
    }

    std::any visitLit(SVParser::LitContext *context) override
    {
        return {};
    }

    std::any visitVar(SVParser::VarContext *context) override
    {
        return {};
    }

    std::any visitNot(SVParser::NotContext *context) override
    {
        return {};
    }

    std::any visitBitwise_not(SVParser::Bitwise_notContext *context) override
    {
        return {};
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
    std::map<std::string, Register> registers;

    void declare_register(const std::string& name, const std::size_t width)
    {
        if constexpr (DebugMessages)
            std::cout << "Instance of register " << name << std::endl;

        registers[name] = {name, width};
    }

    void declare_wire(const std::string& name, const std::size_t width)
    {
        if constexpr (DebugMessages)
            std::cout << "Instance of wire " << name << std::endl;
    }
};

using ModuleVisitorDebug = ModuleVisitorImpl<true>;
using ModuleVisitor = ModuleVisitorImpl<false>;
