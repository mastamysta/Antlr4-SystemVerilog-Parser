#pragma once

#include <variant>
#include <string>
#include <utility>

namespace simulator
{

struct Brackets;
struct BitwiseNot;
struct LogicalNot;
struct Divide;
struct Multiply;
struct Add;
struct Subtract;
struct SignalReference;
struct Literal;

using Expression = std::variant<Brackets,
                                BitwiseNot,
                                LogicalNot,
                                Divide,
                                Multiply,
                                Add,
                                Subtract,
                                SignalReference,
                                Literal>;


struct Brackets
{
    constexpr explicit Brackets(std::unique_ptr<Expression>&& expr):
        m_expr{std::move(expr)}
    {

    }

    std::unique_ptr<Expression> m_expr;
};

struct BitwiseNot
{
    constexpr explicit BitwiseNot(std::unique_ptr<Expression>&& expr):
        m_expr{std::move(expr)}
    {

    }

    std::unique_ptr<Expression> m_expr;
};

struct LogicalNot
{
    constexpr explicit LogicalNot(std::unique_ptr<Expression>&& expr):
        m_expr{std::move(expr)}
    {

    }

    std::unique_ptr<Expression> m_expr;
};

struct Divide
{
    constexpr explicit Divide(std::unique_ptr<Expression>&& lhs,
                                std::unique_ptr<Expression>&& rhs):
        m_lhs{std::move(lhs)},
        m_rhs{std::move(rhs)}
    {

    }

    std::unique_ptr<Expression> m_lhs;
    std::unique_ptr<Expression> m_rhs;
};

struct Multiply
{
    constexpr explicit Multiply(std::unique_ptr<Expression>&& lhs,
                                std::unique_ptr<Expression>&& rhs):
        m_lhs{std::move(lhs)},
        m_rhs{std::move(rhs)}
    {

    }

    std::unique_ptr<Expression> m_lhs;
    std::unique_ptr<Expression> m_rhs;
};

struct Add
{
    constexpr explicit Add(std::unique_ptr<Expression>&& lhs,
                                std::unique_ptr<Expression>&& rhs):
        m_lhs{std::move(lhs)},
        m_rhs{std::move(rhs)}
    {

    }

    std::unique_ptr<Expression> m_lhs;
    std::unique_ptr<Expression> m_rhs;
};

struct Subtract
{
    constexpr explicit Subtract(std::unique_ptr<Expression>&& lhs,
                                std::unique_ptr<Expression>&& rhs):
        m_lhs{std::move(lhs)},
        m_rhs{std::move(rhs)}
    {

    }

    std::unique_ptr<Expression> m_lhs;
    std::unique_ptr<Expression> m_rhs;
};

struct SignalReference
{
    constexpr explicit SignalReference(std::string signal_name):
        m_signal_name{signal_name}
    {

    }

    std::string m_signal_name;
};

struct Literal
{
    constexpr explicit Literal(std::string value):
        m_value{value}
    {

    }
    
    std::string m_value;
};

}
