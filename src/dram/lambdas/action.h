#ifndef KIMULATOR_LAMBDA_ACTION_H
#define KIMULATOR_LAMBDA_ACTION_H
#include "base/type.h"
#include "spdlog/spdlog.h"
namespace Kimulator
{
    namespace Lambdas
    {
        namespace Action
        {

            namespace Bank
            {
                template <typename T>
                void act(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    node->m_state = T::m_states["Opened"];
                    node->m_row_state[target_id] = T::m_states["Opened"];
                }
                template <typename T>
                void pre(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    node->m_state = T::m_states["Closed"];
                    node->m_row_state.clear();
                }

            }

            namespace BankGroup
            {
                // search target bank from a whole rank and precharge it
                template <typename T>
                void PREsb(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    typename T::Node *rank = node->m_parent_node;
                    for (auto bank_group : rank->m_child_nodes)
                    {
                        for (auto bank : bank_group->m_child_nodes)
                        {
                            if (bank->m_node_id == target_id)
                            {
                                bank->m_state = T::m_states["Closed"];
                                bank->m_row_state.clear();
                            }
                        }
                    }
                }
                // sequence cmd in a same bank
                template <typename T>
                void SameBankActions(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    typename T::Node *rank = node->m_parent_node;
                    for (auto bank_group : rank->m_child_nodes)
                    {
                        for (auto bank : bank_group->m_child_nodes)
                        {
                            if (bank->m_node_id == target_id)
                            {
                                bank->update_time(cmd, target_id, clk);
                            }
                        }
                    }
                }
            }
            namespace Rank
            {
                // precharge all banks in current rank node
                template <typename T>
                void PREab(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    if (T::m_levels["rank"] - T::m_levels["bank"] == 2)
                    {
                        // rank->bank_groups->banks
                        for (auto bank_group : node->m_child_nodes)
                        {
                            for (auto bank : bank_group->m_child_nodes)
                            {
                                bank->m_state = T::m_states["Closed"];
                                bank->m_row_state.clear();
                            }
                        }
                    }
                    else if (T::m_levels["rank"] - T::m_levels["bank"] == 1)
                    {
                        // rank -> banks
                        for (auto bank : node->m_child_nodes)
                        {
                            bank->m_state = T::m_states["Closed"];
                            bank->m_row_state.clear();
                        }
                    }
                    else
                    {
                        // unvalid org
                        // throw ConfigurationError("error organization");
                        spdlog::error("error organization!");
                    }
                }
                // search a target bank and precharge
                template <class T>
                void PREsb(typename T::Node *node, int cmd, int target_id, Clk_t clk)
                {
                    for (auto bank_group : node->m_child_nodes)
                    {
                        for (auto bank : bank_group->m_child_nodes)
                        {
                            if (bank->m_node_id == target_id)
                            {
                                bank->m_state = T::m_states["Closed"];
                                bank->m_row_state.clear();
                            }
                        }
                    }
                }
            }
            namespace Channel
            {
            }
        }
    }
}
#endif