#ifndef KIMULATOR_DRAM_REFRESHER_H
#define KIMULATOR_DRAM_REFRESHER_H
namespace Kimulator
{
    class IRefresher
    {
    public:
        virtual void tick() = 0;
    };
}
#endif