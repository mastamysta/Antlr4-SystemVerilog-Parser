#pragma once

#include <variant>

namespace simulator
{

struct Assignment
{

};

struct If
{
    explicit If(std::string condition,
                std::vector<Assignment> assignments):
        m_condition{condition},
        m_assignments{assignments}
    {
        
    }

    std::string m_condition;
    std::vector<Assignment> m_assignments;
};

}
