#pragma once

#include <string>

#include "ast/Generic.hpp"

namespace simulator
{

struct PortDecl
{
    enum class PortDeclDirection
    {
        IN,
        OUT,
        INOUT // Not implemented yet.
    };

    explicit PortDecl(std::string name, 
                        PortDeclDirection direction,
                        NetType type):
        m_name{name},
        m_direction{direction},
        m_type{type}
    {

    }

    NetType m_type;
    PortDeclDirection m_direction;
    std::string m_name;
};

}