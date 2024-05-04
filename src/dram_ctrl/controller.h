#ifndef KIMULATOR_DRAM_CONTROLLER_H
#define KIMULATOR_DRAM_CONTROLLER_H

#include "dram/dram.h"
#include "dram_ctrl/refresher.h"
#include "dram_ctrl/scheduler.h"
#include "base/request.h"
namespace Kimulator
{
    class IDRAMController
    {

    public:
        IDRAM *m_dram;
        IScheduler *m_scheduler;
        IRefresher *m_refresher;

        int channel_id; // channel for controller

    public:
        /**
         * @brief           Send a request to memory controller
         *
         * @param req       The request to be enqueue
         * @return true     Successful
         * @return false    Failed (caused by constraints)
         */

        virtual bool send(Request &req);
        /**
         * @brief  Send a prioritized-request to memory controller
         *
         * @param req       The request to be enqueue
         * @return true     Successful
         * @return false    Failed
         */

        virtual bool priority_send(Request &req);
        /**
         * @brief           Tick for memory controller
         *
         */
        virtual void tick();
    };
}
#endif