#include "dram_ctrl/controller.h"
#include <deque>
namespace Kimulator
{

    class Controller : public IDRAMController
    {

    public:
        std::deque<Request> RPending;
        RBuffer active_buffer;
        RBuffer priority_buffer;
        RBuffer read_buffer;
        RBuffer write_buffer;

        float wr_high_watermark;
        float wr_low_watermark;
        bool is_wirte_mode = false;

    public:
        void init()
        {
            wr_high_watermark = 0.2f;
            wr_low_watermark = 0.8f;

            m_scheduler = create_scheduler();
            m_refresher = create_refresher();
        }
        // implementing send
        bool send(Request &req) override
        {
            if (req.type_id == Request::type_read)
            {
                // check if same addr existing in write_buffer, pend incoming read request if yes.
                if (write_buffer.containAddr(req))
                {
                    RPending.push_back(req);
                    return true;
                }
                else
                {
                    // push back to read buffer
                    return read_buffer.enqueue(req);
                }
            }
            else
            {
                return write_buffer.enqueue(req);
            }
        }
        bool priority_send(Request &req) override
        {
            return priority_buffer.enqueue(req);
        }

    private:
        void create_scheduler(){};
        void create_refresher(){};
        // check write buffer with watermark
        void set_write_mode()
        {
            if (!is_wirte_mode && (read_buffer.size() == 0 || write_buffer.size() > write_buffer.size() * wr_high_watermark))
            {
                is_wirte_mode = true;
                return;
            }
            if (is_wirte_mode && (read_buffer.size() > 0 && write_buffer.size() < write_buffer.size() * wr_low_watermark))
            {
                is_wirte_mode = false;
            }
        }
        // find a request from all request buffer by the order of active >> priority >> read & write
        bool schedule_request(RBuffer bf, Request output)
        {
            // 1.search from active buffer being served
            Request *req = nullptr;
            if (req = m_scheduler->get_prefered_request(active_buffer); req != nullptr)
            {
                if (m_dram->check_ready(req->command, req->addr_vec))
                {
                    bf = &active_buffer;
                    output = &req;
                    return true;
                }
            }
            // 2. search from priority buffer
            if (priority_buffer.size() > 0)
            {
                if (req = m_scheduler->get_prefered_request(priority_buffer); req != nullptr)
                {
                    if (m_dram->check_ready(req.command, req.addr_vec))
                    {
                        bf = &priority_buffer;
                        output = req;
                        return true;
                    }
                }
            }
            // 3.search from read or write buffer
            set_write_mode();
            RBuffer *rdwr = is_wirte_mode ? &write_buffer : &read_buffer;
            if (req = m_scheduler->get_prefered_request(rdwr); req != nullptr)
            {
                if (m_dram->check_ready(req.command, req.addr_vec))
                {
                    bf = &priority_buffer;
                    output = req;
                    return true;
                }
            }
            return false;
        }
    }
}