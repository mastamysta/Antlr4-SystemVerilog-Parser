#pragma once

#include <cstdint>

#include "Signal.hpp"
#include "SimulationState.hpp"

namespace simulator
{

class ModuleSimulator
{
public:
    ModuleSimulator(const SignalMap& signals);

    void simulate(std::size_t cycles);

private:
    uint64_t m_time = 0;
    bool m_clk_val = 0;

    SimulationState m_state;

    void advance_time();
};

}
