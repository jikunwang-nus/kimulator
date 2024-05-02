#ifndef KIMULATOR_LAMBDA_PREQ_H
#define KIMULATOR_LAMBDA_PREQ_H
#include "base/type.h"

namespace Kimulator
{
    namespace Lambdas
    {
        namespace Preq
        {
            namespace Bank
            {
                // if bank not open, then ACT bank first; If row not hit, open row first
                template <typename T>
                int RequireRowOpen(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    if (node->m_state != T::m_states["Opened"])
                    {
                        return T::m_commands["ACT"];
                    }
                    if (node->m_row_state.find(target_id) == node->m_row_state.end())
                    {
                        return T::m_commands["PRE"];
                    }
                    return cmd;
                }
                template <class T>
                int RequireBankClosed(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    if (node->m_state == T::m_states["Closed"])
                        return cmd;
                    return T::m_commands["PRE"];
                };
            }

            namespace BankGroup
            {
            }
            namespace Rank
            {
            }
            namespace Channel
            {
            }
        }
    }
}
#endif