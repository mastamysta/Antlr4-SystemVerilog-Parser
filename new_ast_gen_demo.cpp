#include <iostream>
#include <cstdlib>

#include "ast/generator/Antlr4ASTGenVisitor.hpp"

int main(const int argc, const char *argv[])
{
    auto visitor = simulator::Antlr4ASTGenVisitor{};
    visitor.visitDesign("/home/bread/sim/design.sv");

    return EXIT_SUCCESS;
}
