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
    SignalMap m_signals_a; 
    SignalMap m_signals_b;

    SimulationState m_state;

    void set_signal_eval(const std::string& signal, const auto& eval_func);

    auto& get_current_state();

    auto& get_next_state();

    void advance_time();
};

}
