#pragma once

#include <utility>

#include "Expression.hpp"

namespace simulator
{

enum class SensitivityType
{
    POSEDGE,
    NEGEDGE
};

struct Sensitivity
{
    explicit Sensitivity(Expression&& sens_expression,
                         SensitivityType sensitivity_type):
        m_sensitivity_type{sensitivity_type},
        m_sens_expression{std::move(sens_expression)}
    {
        
    }

    SensitivityType m_sensitivity_type;
    Expression m_sens_expression;
};

}
