#ifndef KIMULATOR_BASE_TYPE_H
#define KIMULATOR_BASE_TYPE_H
#include <type_traits>
#include <vector>
namespace Kimulator
{
    using Clk_t = int64_t;
    using Addr_t = int64_t; // Plain address as seen by the OS
    using AddrVec_t = std::vector<int>;
}
#endif
