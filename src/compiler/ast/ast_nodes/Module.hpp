#pragma once

#include <vector>
#include <string>

#include "ast/ast_nodes/PortDecl.hpp"
#include "ast/ast_nodes/Always.hpp"
#include "ast/ast_nodes/SyncProc.hpp"
#include "ast/ast_nodes/Initial.hpp"
#include "ast/ast_nodes/LogicDecl.hpp"
#include "ast/ast_nodes/WireDecl.hpp"

namespace simulator
{

struct Module
{
    std::string m_name;
    std::vector<PortDecl> m_port_declarations;
    std::vector<Initial> m_initials;
    std::vector<Always> m_always;
    std::vector<SyncProc> m_sync_procs;
    std::vector<WireDecl> m_wire_decls;
    std::vector<LogicDecl> m_logic_decls;

};

}
