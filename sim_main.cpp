#include <iostream>

#include <antlr4-runtime.h>

#include "SVLexer.h"
#include "SVParser.h"
#include "SVVisitor.h"


class ModuleVisitor : public SVVisitor
{
public:

    std::any visitModule(SVParser::ModuleContext *context) override
    {
        return {};
    }

    std::any visitModule_header(SVParser::Module_headerContext *context) override
    {
        return {};
    }

    std::any visitPorts(SVParser::PortsContext *context) override
    {
        return {};
    }

    std::any visitPort(SVParser::PortContext *context) override
    {
        return {};
    }

    std::any visitModule_body(SVParser::Module_bodyContext *context) override
    {
        return {};
    }

    std::any visitModule_block(SVParser::Module_blockContext *context) override
    {
        return {};
    }

    std::any visitSync_proc(SVParser::Sync_procContext *context) override
    {
        return {};
    }

    std::any visitSignal_trans(SVParser::Signal_transContext *context) override
    {
        return {};
    }

    std::any visitBlock_body(SVParser::Block_bodyContext *context) override
    {
        return {};
    }

    std::any visitIf_block(SVParser::If_blockContext *context) override
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
};

int main(const int argc, const char *argv[])
{
    std::cout << "Reading in design." << std::endl;
    
    auto stream = std::ifstream{};
    stream.open("/home/bread/sim/design.sv");
    
    auto input = antlr4::ANTLRInputStream{stream};
    auto lexer = SVLexer{&input};
    auto tokens = antlr4::CommonTokenStream{&lexer};
    auto parser = SVParser{&tokens};    
    auto tree = parser.module();

    auto irv = ModuleVisitor{};
 
    irv.visitModule(tree);
}
