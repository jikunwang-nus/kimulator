
#include "dram_ctrl/scheduler.h"
#include "dram/dram.h"
namespace Kimulator
{
    class FRFCFSScheduler : public IScheduler
    {
    private:
        IDRAM *m_dram;

    public:
        Request *compare(Request *src, Request *target)
        {
            // check if request src and target are ready
            bool src_ready = m_dram->check_ready(src->command, src->addr_vec);
            bool target_ready = m_dram->check_ready(target->command, target->addr_vec);
            if (src_ready && target_ready)
            {
                if (src->arrive < target->arrive)
                    return src;
                return target;
            }
            if (src_ready)
                return src;
            if (target_ready)
                return target;
            // neither src no target ready, compare arrive directly
            if (src->arrive <= target->arrive)
                return src;
            else
                return target;
        }
        Request *get_prefered_request(RBuffer &buffer)
        {
            if (buffer.size() == 0)
                return nullptr;
            Request *choice = buffer.begin();

            for (auto at = buffer.begin(); at != buffer.end(); at++)
            {
                choice = compare(choice, at)
            }
            return choice;
        }
    }
}