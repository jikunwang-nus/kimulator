#ifndef KIMULATOR_BASE_REQUEST_H
#define KIMULATOR_BASE_REQUEST_H

#include "base/type.h"
#include <list>
using namespace std;
namespace Kimulator
{
    class Request
    {
    public:
        Addr_t addr;
        AddrVec_t addr_vec;

    public:
        Request(Addr_t addr, int type);
        Request(AddrVec_t addr_vec, int type);
    }
    // buffer to store requests
    class RBuffer
    {
    public:
        list<Request> buffer;
        size_t max_size = 64;

    public:
        bool enqueue(Request &req)
        {
            if (buffer.size() >= max_size)
                return false;
            buffer.push_back(req) return true;
        }
        void remove(Request &req)
        {
            buffer.remove(req);
        }
    }
}
#endif