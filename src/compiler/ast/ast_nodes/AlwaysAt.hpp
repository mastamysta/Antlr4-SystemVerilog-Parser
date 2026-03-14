#pragma once

#include <string>

#include "Sensitivity.hpp"

namespace simulator
{


struct AlwaysAt
{
    explicit AlwaysAt(Sensitivity sensitivity):
        m_sensitivity(sensitivity)
    {

    }

    Sensitivity m_sensitivity;
};

}
