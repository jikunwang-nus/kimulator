#include "mem_sys/memory_system.h"
#include "dram_ctrl/controller.h"
#include "addr_map/addr_map.h"
#include "base/factory.h"
namespace Kimulator
{
    class DRAMMemorySystem : public IMemorySystem
    {
        REGISTER_IMPLEMENTATION(DRAMMemorySystem, "DRAMMemorySystem", "memory system for generic dram");

    public:
        vector<IDRAMController *> m_controllers;
        IDRAM *m_dram;
        IAddrMapper *m_addr_mapper;
        Clk_t m_clk;
        /**
         * @brief
         *  initialize memory system, including dram, address mapper and dram controllers
         */
        void init()
        {
            m_dram = create_dram();
            m_addr_mapper = create_addr_mapper();
            int channel_count = m_dram->get_level_size("channels");
            for (size_t i = 0; i < channel_count; i++)
            {
                /* code */
                IDRAMController *m_ctrl = create_mem_controller();
                m_ctrl->channel_id = i;
                m_controllers.push_back(m_ctrl);
            }
        }
        bool send(Request req) override
        {
            // address translation
            m_addr_mapper->map(req);
            // calculate channel id and choose controller to send
            int channel_id = req.addr_vec[0];
            return m_controllers[channel_id]->send(req);
        }
        void tick()
        {
            m_clk++;
            m_dram->tick();
            // tick controllers
            for (auto ct : m_controllers)
            {
                ct->tick();
            }
        }
    }
} // namespace Kimulator
