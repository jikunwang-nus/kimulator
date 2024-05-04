#ifndef KIMULATOR_MEM_SYS_H
#define KIMULATOR_MEM_SYS_H

#include "base/request.h"
#include "base/factory.h"
namespace Kimulator
{
    /**
     * @brief This a interface of memory system, defining general action
     *
     */
    class IMemorySystem
    {
        REGISTER_INTERFACE(IMemorySystem, "IMemorySystem", "memory system interface");
        virtual bool send(Request req);
    }
}
#endif