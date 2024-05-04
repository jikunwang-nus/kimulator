#ifndef KIMULATOR_DRAM_SCHEDULER_H
#define KIMULATOR_DRAM_SCHEDULER_H
#include "base/request.h"
namespace Kimulator
{
    class IScheduler
    {
    public:
        virtual Request *get_prefered_request(RBuffer &buffer);
    };
}
#endif