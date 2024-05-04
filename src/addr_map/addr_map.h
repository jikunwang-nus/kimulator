#ifndef KIMULATOR_ADDR_MAP_H
#define KIMULATOR_ADDR_MAP_H
#include "base/request.h"
class IAddrMapper
{
public:
    /**
     * @brief
     *  receive a request and modify virtual address inside to physical address
     * @param req
     */
    virtual void map(Request &req);
}
#endif