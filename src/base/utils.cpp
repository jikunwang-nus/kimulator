#include "utils.h"
namespace Kimulator
{
    uint64_t JEDEC_rounding(float t_ns, int tCK_ps)
    {
        // Turn timing in nanosecond to picosecond
        uint64_t t_ps = t_ns * 1000;

        // Apply correction factor 974
        uint64_t nCK = ((t_ps * 1000 / tCK_ps) + 974) / 1000;
        return nCK;
    }
}