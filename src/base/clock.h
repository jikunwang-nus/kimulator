#ifndef KIMULATOR_BASE_CLOCK_H
#define KIMULATOR_BASE_CLOCK_H
#include "base/type.h"
namespace Kimulator
{
    template <class T>
    class Clock
    {
        friend T;

    protected:
        Clk_t m_clk;

    public:
        void tcik(){
            //    need to implement by target class
        };
    };
}
#endif