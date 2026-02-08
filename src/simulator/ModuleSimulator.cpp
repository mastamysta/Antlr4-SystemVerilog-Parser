#include <iostream>

#include "ModuleSimulator.hpp"

namespace simulator
{


ModuleSimulator::ModuleSimulator(const SignalMap& signals): 
                                        m_signals_a(signals),
                                        m_signals_b(signals),
                                        m_state(signals)
{ 
}

void ModuleSimulator::simulate(std::size_t cycles)
{
    m_state.immediate_assign("rstn", 0);

    advance_time();

    m_state.immediate_assign("rstn", 1);

    for (auto i{0ul}; i < cycles; i++)
    {
        advance_time();
    }
}


void ModuleSimulator::advance_time()
{
    std::cout << "Time is " << m_time <<  std::endl;

    int curr_clk = m_clk_val;

    m_state.immediate_assign("clk", m_clk_val);

    for (const auto& dependent: m_state.get_dependent_signals("clk"))
    {
        m_state.evolve_signal(dependent);
    }

    m_state.retire_changes();

    ++m_time;
    m_clk_val = !m_clk_val;
    std::cout << std::endl << std::endl;
}


}
