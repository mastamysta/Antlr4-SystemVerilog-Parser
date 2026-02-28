#pragma once

#include <string>

namespace simulator
{

struct Sensitivity
{
    explicit Sensitivity(std::string signal):
        m_signal{signal}
    {
        
    }

    std::string m_signal;
};

}
