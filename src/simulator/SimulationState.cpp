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
    m_buffered_signals.insert(signal);
}

auto SimulationState::retire_changes() -> void
{
    m_current_state = m_next_state;

    if (!m_buffered_signals.size())
        return;

    const auto buffered_signals_copy = std::move(m_buffered_signals);
    m_buffered_signals.clear();

    evolve_dependents_of_retirees(buffered_signals_copy);
}

auto SimulationState::evolve_dependents_of_retirees(const std::set<std::string>& retirees) -> void
{
    for (const auto& signal: retirees)
        for (const auto& dependent: get_dependent_signals(signal))
            evolve_signal(dependent);

    retire_changes();
}

auto SimulationState::evolve_signal(const std::string& signal) -> void
{
    const auto new_value = m_current_state[signal].m_next_value(m_current_state);
    
    // If is blocking assignment:
    blocking_assign(signal, new_value);

    std::cout << signal << " has new value " << new_value << std::endl;
}

auto SimulationState::get_dependent_signals(const std::string& signal) -> const std::set<std::string>&
{
    return m_current_state[signal].m_dependent_signals;
}


}
