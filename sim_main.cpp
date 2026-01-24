#include <iostream>

#include "ModuleVisitor.hpp"

int main(const int argc, const char *argv[])
{
    auto visitor = ModuleVisitorDebug{};
    visitor.visitDesign();

    return 0;
}
