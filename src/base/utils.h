#ifndef KIMULATOR_BASE_UTILS_H
#define KIMULATOR_BASE_UTILS_H
#include <cstdint>

namespace Kimulator
{
    uint64_t JEDEC_rounding(float t_ns, int tCK_ps);
}
#endif