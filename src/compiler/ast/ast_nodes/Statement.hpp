#pragma once

#include <variant>
#include <vector>
#include <utility>

#include "Expression.hpp"

namespace simulator
{

struct Assignment
{
    SignalReference m_target;
    Expression m_assigned_expression;
};

struct If
{
    explicit If(Expression&& condition,
                std::vector<Assignment> assignments):
        m_condition{std::move(condition)},
        m_assignments{assignments}
    {
        
    }

    Expression m_condition;
    std::vector<Assignment> m_assignments;
};

}
