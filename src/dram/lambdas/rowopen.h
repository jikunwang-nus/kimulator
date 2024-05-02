#ifndef KIMULATOR_DRAM_LAMBDA_ROWOPEN_H
#define KIMULATOR_DRAM_LAMBDA_ROWOPEN_H

#include "base/type.h"
namespace Kimulator
{
    namespace Lambdas
    {
        namespace RowOpen
        {
            namespace Bank
            {
                // bank open state needed before read and write
                template <typename T>
                bool RDWR(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    if (node->m_state != T::m_states["Opened"])
                    {
                        return false;
                    }
                    return true;
                }
            }
        }
    }
}
#endif