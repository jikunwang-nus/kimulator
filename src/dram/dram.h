#include "spec.h"

namespace Kimulator {
    // define abstract class IDRAM as root class, all impl should implement public function
    // 
    
    class IDRAM{
    /**+++++++++++++++++++++++++++++++++++++++
        Organization
        1. internel prefetch size
        2. memory level
        3. organization
        4. channel width
    **+++++++++++++++++++++++++++++++++++++*/
    public:
        int m_internel_prefetch_size = -1;
        specification sepc;
        int channel_width = -1;

    /**+++++++++++++++++++++++++++++++++++++++++
        Request & Commands:
        1. commands
        2. requests
    +++++++++++++++++++++++++++++++++++++++++**/
    public:
         Arraylist commands;
         Arraylist requests;
    /**
     * Node status
     * 
     * */

    /**
     * Timing
     * 
     */
    // Timing

    /**
     * @brief 
     * 
     */
    // Device interface
    };
}