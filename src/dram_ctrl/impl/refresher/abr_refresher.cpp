#include "dram_ctrl/refresher.h"
#include "base/type.h"
#include "dram/dram.h"
#include "dram_ctrl/controller.h"
namespace Kimulator
{

    class ABRRefresher : public IRefresher
    {
    private:
        Clk_t m_clk;
        IDRAM *m_dram;            // memory
        IDRAMController *m_ctrl;  // memory controller
        int m_rank_num;           // number of banks
        int m_refi;               // interval of refresh
        int m_next_refresh_cycle; // next refresh clk
        int m_ref_req_id;

    public:
        void set()
        {
            m_dram = m_ctrl->m_dram;
            m_rank_num = m_dram->get_level_size("rank");
            m_refi = m_dram->m_timings_ct.value("nREFI");
            m_next_refresh_cycle = m_nrefi;
            m_ref_req_id = m_dram->m_requests("all-bank-refresh");
        }
        void tick()
        {
            m_clk++;
            if (m_clk == m_next_refresh_cycle)
            {
                // exec refresh, traverse every rank
                for (int i = 0; i < m_rank_num; i++)
                {
                    // assemble request, just load channel_id and bank_id
                    AddrVec_t av(2);
                    av[0] = m_ctrl->channel_id;
                    av[1] = i;
                    Request req(av, m_ref_req_id);
                    // @todo address failure
                    m_ctrl->priority_send(req);
                }
            }
        }
    }
}