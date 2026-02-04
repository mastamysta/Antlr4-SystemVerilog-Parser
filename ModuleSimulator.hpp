#pragma once

#include "Signal.hpp"

class ModuleSimulator
{
public:
    ModuleSimulator(const Signal::SignalMap& signals): m_signals_a(signals), m_signals_b(signals)
    { 
    }

    void simulate(std::size_t cycles)
    {
        // For now just set initial value of rstn to 0.
        set_signal_eval("rstn", [](Signal::SignalMap){ return 0; });

        advance_time();

        set_signal_eval("rstn", [](Signal::SignalMap){ return 1; });

        for (auto i{0ul}; i < cycles; i++)
        {
            advance_time();
        }
    }

private:
    uint64_t m_time = 0;
    bool m_clk_val = 0;
    Signal::SignalMap m_signals_a; // Initial state of system.
    Signal::SignalMap m_signals_b;

    auto set_signal_eval(const std::string& signal, const auto& eval_func) -> void
    {
        get_current_state()[signal].m_eval = eval_func;
        get_next_state()[signal].m_eval = eval_func;
    }

    auto& get_current_state()
    {
        if (m_time & 0x1)
            return m_signals_b;
        else
            return m_signals_a;
    }

    auto& get_next_state()
    {
        if (m_time & 0x1)
            return m_signals_a;
        else
            return m_signals_b;
    }

    void advance_time()
    {
        std::cout << "Time is " << m_time <<  std::endl;

        auto& current_state = get_current_state();
        auto& next_state = get_next_state();

        int curr_clk = m_clk_val;

        current_state["clk"].m_eval = [curr_clk](Signal::SignalMap) { return curr_clk; };

        for (const auto& dependent: current_state["clk"].m_dependent_signals)
        {
            const auto next_value = current_state[dependent].m_next_value(current_state);
            next_state[dependent].m_eval = [next_value](Signal::SignalMap){ return next_value; };

            std::cout << dependent << " has new value " << next_value << std::endl;
        }

        ++m_time;
        m_clk_val = !m_clk_val;
        std::cout << std::endl << std::endl;
    }
};
