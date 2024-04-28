#ifndef KIMULATOR_DRAM_DRAM_H
#define KIMULATOR_DRAM_DRAM_H

#include "spec.h"
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
        specification m_spec;
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

        /**
         * Timing
         *
         */
        Kcontainer<string, int> m_timings_ct; // timing names
        int64_t m_read_latency;
        /**
         * @brief
         *
         */
        // Device interface
    };
}
#endif