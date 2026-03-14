#pragma once

#include <vector>

#include "Sensitivity.hpp"
#include "Statement.hpp"

namespace simulator
{

struct SyncProc
{
    explicit SyncProc(Sensitivity sensitivity,
                      std::vector<If> ifs,
                      std::vector<Assignment> assignments):
        m_sensitivity{sensitivity},
        m_ifs{ifs},
        m_assignments{assignments}
    {
        
    }

    Sensitivity m_sensitivity;
    std::vector<If> m_ifs;
    std::vector<Assignment> m_assignments;
};

}
