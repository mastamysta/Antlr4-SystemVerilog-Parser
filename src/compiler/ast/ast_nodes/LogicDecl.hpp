#pragma once

#include <string>

namespace simulator
{

struct LogicDecl
{
    explicit LogicDecl(std::string name):
        m_name{name}
    {
        
    }
    
    std::string m_name;
};

}
