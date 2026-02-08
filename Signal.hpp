#pragma once

#include <functional>
#include <vector>

namespace simulator
{

struct Signal;

using SignalID = std::size_t;
using SignalWidth = std::size_t;
using SignalMap = std::map<std::string, Signal>;
using SignalEvaluationFunction = std::function<int(const SignalMap&)>;

enum class SignalType
{
    WIRE,
    REG
};

struct Signal
{
    SignalID m_id;
    SignalEvaluationFunction m_eval;
    SignalType m_type;
    std::set<std::string> m_dependent_signals;
    SignalEvaluationFunction m_next_value;
};

}
