#pragma once

#include <functional>

struct Signal
{
    enum SignalType
    {
        WIRE,
        REG
    };

    using SignalID = std::size_t;
    using SignalWidth = std::size_t;
    using SignalMap = std::map<std::string, Signal>;
    using SignalEvaluationFunction = std::function<int(const SignalMap&)>;

    SignalID m_id;
    SignalEvaluationFunction m_eval;
    SignalType m_type;
};
