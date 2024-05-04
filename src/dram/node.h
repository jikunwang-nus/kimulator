#ifndef KIMULATOR_DRAM_NODE_H
#define KIMULATOR_DRAM_NODE_H

#include <type_traits>
#include "dram/spec.h"
#include "base/type.h"
#include <deque>
using namespace std;
namespace Kimulator
{
    class IDRAM;
    // template <typename T>
    // concept IsDRAMSpec = requires(T t) {
    //     typename T::Node;
    // };
    template <class T>
    using Func_void = std::function<void(typename T::Node *node, int cmd, int target_id, Clk_t clk)>;
    template <class T>
    using Func_int = std::function<int(typename T::Node *node, int cmd, int target_id, Clk_t clk)>;
    template <class T>
    using Func_bool = std::function<bool(typename T::Node *node, int cmd, int target_id, Clk_t clk)>;

    template <typename T>
    using FuncVV = std::vector<std::vector<T>>;

    template <typename T>
    concept IsDRAMSpec = requires(T t) {
        typename T::Node;
    };
    template <IsDRAMSpec T>
    class DRAMNodeBase
    {
    public:
        using NodeType = typename T::Node;
        T *m_spec = nullptr;
        NodeType *m_parent_node = nullptr;
        std::vector<NodeType *> m_child_nodes;

        int m_level = -1;   // The level of this node in the organization hierarchy
        int m_node_id = -1; // The id of this node at this level
        int m_size = -1;    // The size of the node (e.g., how many rows in a bank)

        int m_state = -1;                   // The state of the node
        std::vector<Clk_t> m_cmd_ready_clk; // The next cycle that each command can be issued again at this level
        vector<deque<Clk_t>> m_cmd_history; // Issue-history of each command at this level
        using RowId_t = int;
        using RowState_t = int;
        std::map<RowId_t, RowState_t> m_row_state;
        DRAMNodeBase(T *spec, NodeType *parent, int level, int id) : m_spec(spec), m_parent_node(parent), m_level(level), m_node_id(id)
        {
            int num_cmds = T::m_commands.size();
            m_cmd_ready_clk.resize(num_cmds, -1);
            m_cmd_history.resize(num_cmds);
            for (int cmd = 0; cmd < num_cmds; cmd++)
            {
                int window = 0;
                for (const auto &t : spec->m_timing_cons[level][cmd])
                {
                    window = std::max(window, t.window);
                }
                if (window != 0)
                {
                    m_cmd_history[cmd].resize(window, -1);
                }
                else
                {
                    m_cmd_history[cmd].clear();
                }
            }

            m_state = spec->m_init_states[m_level];

            // Recursively construct next levels
            int next_level = level + 1;
            int last_level = T::m_levels["row"];
            if (next_level == last_level)
            {
                return;
            }
            else
            {
                int next_level_size = m_spec->m_organization.count[next_level];
                if (next_level_size == 0)
                {
                    return;
                }
                else
                {
                    for (int i = 0; i < next_level_size; i++)
                    {
                        NodeType *child = new NodeType(spec, static_cast<NodeType *>(this), next_level, i);
                        static_cast<NodeType *>(this)->m_child_nodes.push_back(child);
                    }
                }
            }
        };

    public:
        bool check_ready(int command, const AddrVec_t &addr_vec, Clk_t clk)
        {
            if (m_cmd_ready_clk[command] != -1 && clk < m_cmd_ready_clk[command])
            {
                // stop recursion: the check failed at this level
                return false;
            }

            int child_id = addr_vec[m_level + 1];
            if (child_id < 0 || m_level == m_spec->m_command_scopes[command] || !m_child_nodes.size())
            {
                // stop recursion: the check passed at all levels
                return true;
            }

            // recursively check my child
            return m_child_nodes[child_id]->check_ready(command, addr_vec, clk);
        };
    };
}
#endif