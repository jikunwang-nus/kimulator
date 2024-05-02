#include "dram_ctrl/controller.h"

namespace Kimulator {

    class Controller : public IDRAMController {
        public: 

        RBuffer active_buffer;
        RBuffer priority_buffer;
        RBuffer read_buffer;
        RBuffer write_buffer;
        
    }
}