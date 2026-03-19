#pragma once

#include <string>

#include "Sensitivity.hpp"
#include "Statement.hpp"

namespace simulator
{


struct AlwaysAt
{
    explicit AlwaysAt(Sensitivity sensitivity):
        m_sensitivity(sensitivity)
    {

    }

    std::vector<If> ifs;
    std::vector<Assignment> assignments;

    Sensitivity m_sensitivity;
};

}
