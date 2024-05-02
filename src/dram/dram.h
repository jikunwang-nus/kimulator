#ifndef KIMULATOR_DRAM_DRAM_H
#define KIMULATOR_DRAM_DRAM_H

#include "dram/spec.h"
namespace Kimulator
{
    // define abstract class IDRAM as root class, all impl should implement public function
    //

    class IDRAM
    {
        /**+++++++++++++++++++++++++++++++++++++++
            Organization
            1. internel prefetch size
            2. memory level
            3. organization
            4. channel width
        **+++++++++++++++++++++++++++++++++++++*/
    public:
        int m_internel_prefetch_size = -1;
        Organization m_organization;
        int m_channel_width = -1;

        /**+++++++++++++++++++++++++++++++++++++++++
            Request & Commands:
            1. commands
            2. requests
        +++++++++++++++++++++++++++++++++++++++++**/

        /**
         * Node status
         *
         * */
        KVector<string> m_states;
        // SpecLUT<State_t> m_init_states{m_states};
        /**
         * Timing
         *
         */
        Kcontainer<string, int> m_timings_ct; // timing names
        int64_t m_read_latency;
        TimingCons m_timing_cons; // The actual timing constraints used by Ramulator's DRAM model

        /**
         * @brief
         *
         */
        // Device interface
    };
}
#endif