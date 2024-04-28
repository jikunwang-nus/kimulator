#ifndef KIMULATOR_DRAM_NODE_H
#define KIMULATOR_DRAM_NODE_H

#include <type_traits>
#include "spec.h"
using namespace std;
namespace Kimulator
{
    class IDRAM;
    template <typename T>
    concept IsDRAMSpec = requires(T t) {
        typename T::Node;
    };

}
#endif