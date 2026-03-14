#pragma once

#include <string>

namespace simulator
{

enum class SensitivityType
{
    POSEDGE,
    NEGEDGE
};

struct Sensitivity
{
    explicit Sensitivity(std::string signal,
                         SensitivityType sensitivity_type):
        m_sensitivity_type{sensitivity_type},
        m_signal{signal}
    {
        
    }

    SensitivityType m_sensitivity_type;
    std::string m_signal;
};

}
