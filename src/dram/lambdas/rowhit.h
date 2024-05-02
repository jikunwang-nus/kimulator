#ifndef KIMULATOR_LAMBDA_ROWHIT_H
#define KIMULATOR_LAMBDA_ROWHIT_H

#include "base/type.h"

namespace Kimulator
{
    namespace Lambdas
    {
        namespace RowHit
        {
            namespace Bank
            {
                //
                template <typename T>
                bool RDWR(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    if (node->m_state == T::m_states["Opened"] && node->m_row_state.find(target_id) != node->m_row_state.end())
                    {
                        return true;
                    }
                    return false;
                }
            }
        }
    }
}
#endif