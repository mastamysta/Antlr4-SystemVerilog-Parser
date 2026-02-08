#pragma once

#include "Signal.hpp"

namespace simulator
{

class SimulationState
{
public:
    SimulationState(const SignalMap&);

    auto immediate_assign(const std::string&, int) -> void;

    auto blocking_assign(const std::string&, int) -> void;

    auto retire_changes() -> void;

    auto evolve_signal(const std::string& signal) -> void;

    auto get_dependent_signals(const std::string& signal) -> const std::set<std::string>&;
private:

    SignalMap m_current_state;
    SignalMap m_next_state;

};

}
