#include <iostream>

#include "SimulationState.hpp"

namespace simulator
{

SimulationState::SimulationState(const SignalMap& signals):
    m_current_state(signals),
    m_next_state(signals)
{
    
}

auto SimulationState::immediate_assign(const std::string& signal, int value) -> void
{
    blocking_assign(signal, value);
    retire_changes();
}

auto SimulationState::blocking_assign(const std::string& signal, int value) -> void
{
    m_next_state[signal].m_eval = [value](const SignalMap&){ return value; };
}

auto SimulationState::retire_changes() -> void
{
    m_current_state = m_next_state;
}

auto SimulationState::evolve_signal(const std::string& signal) -> void
{
    const auto new_value = m_current_state[signal].m_next_value(m_current_state);
    m_next_state[signal].m_eval = [new_value](const SignalMap&){ return new_value; };
    std::cout << signal << " has new value " << new_value << std::endl;
}

auto SimulationState::get_dependent_signals(const std::string& signal) -> const std::set<std::string>&
{
    return m_current_state[signal].m_dependent_signals;
}


}
