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
        int type_id;
        int command;
        using const type_read = 0;
        using const type_write = 1;

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
        size_t size() { return buffer.size(); }
        bool contain(Request &req)
        {
            auto it = std::find(buffer.begin(), buffer.end(), req);
            if (it != buffer.end())
                return true;
            return false;
        }
        bool containAddr(Request &req)
        {
            auto compare_addr = [src](const Request &target)
            {
                return target.addr == src.addr;
            };
            auto it = std::find_if(buffer.begin(), buffer.end(), compare_addr);
            if (it != buffer.end())
                return true;
            return false;
        }
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