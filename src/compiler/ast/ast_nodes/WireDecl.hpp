#pragma once

#include <string>

namespace simulator
{

struct WireDecl
{
    explicit WireDecl(std::string name):
        m_name{name}
    {
        
    }

    std::string m_name;
};

}
