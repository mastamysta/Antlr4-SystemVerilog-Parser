#include <iostream>

#include "ModuleVisitor.hpp"
#include "ModuleSimulator.hpp"

int main(const int argc, const char *argv[])
{
    auto visitor = ModuleVisitorDebug{};
    visitor.visitDesign();

    auto signals = visitor.get_signals();

    for (const auto& sig: signals)
        std::cout << sig.first << std::endl;

    auto simulator = ModuleSimulator{signals};

    simulator.simulate(10);

    return 0;
}
