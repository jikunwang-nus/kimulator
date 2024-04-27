
#include "../spec.h"
#include "../dram.h"
#include <map>

using namespace std;
namespace Kimulator
{

  class DDR4 : public IDRAM
  {

  public:
    // hierachy for each spec
    inline static const std::map<std::string, specification> spec_preset = {
        //   name         density   DQ   Ch Ra Bg Ba   Ro     Co
        {"DDR4_2Gb_x4", {2 << 10, 4, {1, 1, 4, 4, 1 << 15, 1 << 10}}},
        {"DDR4_2Gb_x8", {2 << 10, 8, {1, 1, 4, 4, 1 << 14, 1 << 10}}},
        {"DDR4_2Gb_x16", {2 << 10, 16, {1, 1, 2, 4, 1 << 14, 1 << 10}}},
        {"DDR4_4Gb_x4", {4 << 10, 4, {1, 1, 4, 4, 1 << 16, 1 << 10}}},
        {"DDR4_4Gb_x8", {4 << 10, 8, {1, 1, 4, 4, 1 << 15, 1 << 10}}},
        {"DDR4_4Gb_x16", {4 << 10, 16, {1, 1, 2, 4, 1 << 15, 1 << 10}}},
        {"DDR4_8Gb_x4", {8 << 10, 4, {1, 1, 4, 4, 1 << 17, 1 << 10}}},
        {"DDR4_8Gb_x8", {8 << 10, 8, {1, 1, 4, 4, 1 << 16, 1 << 10}}},
        {"DDR4_8Gb_x16", {8 << 10, 16, {1, 1, 2, 4, 1 << 16, 1 << 10}}},
        {"DDR4_16Gb_x4", {16 << 10, 4, {1, 1, 4, 4, 1 << 18, 1 << 10}}},
        {"DDR4_16Gb_x8", {16 << 10, 8, {1, 1, 4, 4, 1 << 17, 1 << 10}}},
        {"DDR4_16Gb_x16", {16 << 10, 16, {1, 1, 2, 4, 1 << 17, 1 << 10}}},
    };
    // latency details for each spec
    inline static const std::map<std::string, std::vector<int>> timing_presets = {
        //   name       rate   nBL  nCL  nRCD  nRP   nRAS  nRC   nWR  nRTP nCWL nCCDS nCCDL nRRDS nRRDL nWTRS nWTRL nFAW  nRFC nREFI nCS,  tCK_ps
        {"DDR4_1600J", {1600, 4, 10, 10, 10, 28, 38, 12, 6, 9, 4, 5, -1, -1, 2, 6, -1, -1, -1, 2, 1250}},
        {"DDR4_1600K", {1600, 4, 11, 11, 11, 28, 39, 12, 6, 9, 4, 5, -1, -1, 2, 6, -1, -1, -1, 2, 1250}},
        {"DDR4_1600L", {1600, 4, 12, 12, 12, 28, 40, 12, 6, 9, 4, 5, -1, -1, 2, 6, -1, -1, -1, 2, 1250}},
        {"DDR4_1866L", {1866, 4, 12, 12, 12, 32, 44, 14, 7, 10, 4, 5, -1, -1, 3, 7, -1, -1, -1, 2, 1071}},
        {"DDR4_1866M", {1866, 4, 13, 13, 13, 32, 45, 14, 7, 10, 4, 5, -1, -1, 3, 7, -1, -1, -1, 2, 1071}},
        {"DDR4_1866N", {1866, 4, 14, 14, 14, 32, 46, 14, 7, 10, 4, 5, -1, -1, 3, 7, -1, -1, -1, 2, 1071}},
        {"DDR4_2133N", {2133, 4, 14, 14, 14, 36, 50, 16, 8, 11, 4, 6, -1, -1, 3, 8, -1, -1, -1, 2, 937}},
        {"DDR4_2133P", {2133, 4, 15, 15, 15, 36, 51, 16, 8, 11, 4, 6, -1, -1, 3, 8, -1, -1, -1, 2, 937}},
        {"DDR4_2133R", {2133, 4, 16, 16, 16, 36, 52, 16, 8, 11, 4, 6, -1, -1, 3, 8, -1, -1, -1, 2, 937}},
        {"DDR4_2400P", {2400, 4, 15, 15, 15, 39, 54, 18, 9, 12, 4, 6, -1, -1, 3, 9, -1, -1, -1, 2, 833}},
        {"DDR4_2400R", {2400, 4, 16, 16, 16, 39, 55, 18, 9, 12, 4, 6, -1, -1, 3, 9, -1, -1, -1, 2, 833}},
        {"DDR4_2400U", {2400, 4, 17, 17, 17, 39, 56, 18, 9, 12, 4, 6, -1, -1, 3, 9, -1, -1, -1, 2, 833}},
        {"DDR4_2400T", {2400, 4, 18, 18, 18, 39, 57, 18, 9, 12, 4, 6, -1, -1, 3, 9, -1, -1, -1, 2, 833}},
        {"DDR4_2666T", {2666, 4, 17, 17, 17, 43, 60, 20, 10, 14, 4, 7, -1, -1, 4, 10, -1, -1, -1, 2, 750}},
        {"DDR4_2666U", {2666, 4, 18, 18, 18, 43, 61, 20, 10, 14, 4, 7, -1, -1, 4, 10, -1, -1, -1, 2, 750}},
        {"DDR4_2666V", {2666, 4, 19, 19, 19, 43, 62, 20, 10, 14, 4, 7, -1, -1, 4, 10, -1, -1, -1, 2, 750}},
        {"DDR4_2666W", {2666, 4, 20, 20, 20, 43, 63, 20, 10, 14, 4, 7, -1, -1, 4, 10, -1, -1, -1, 2, 750}},
        {"DDR4_2933V", {2933, 4, 19, 19, 19, 47, 66, 22, 11, 16, 4, 8, -1, -1, 4, 11, -1, -1, -1, 2, 682}},
        {"DDR4_2933W", {2933, 4, 20, 20, 20, 47, 67, 22, 11, 16, 4, 8, -1, -1, 4, 11, -1, -1, -1, 2, 682}},
        {"DDR4_2933Y", {2933, 4, 21, 21, 21, 47, 68, 22, 11, 16, 4, 8, -1, -1, 4, 11, -1, -1, -1, 2, 682}},
        {"DDR4_2933AA", {2933, 4, 22, 22, 22, 47, 69, 22, 11, 16, 4, 8, -1, -1, 4, 11, -1, -1, -1, 2, 682}},
        {"DDR4_3200W", {3200, 4, 20, 20, 20, 52, 72, 24, 12, 16, 4, 8, -1, -1, 4, 12, -1, -1, -1, 2, 625}},
        {"DDR4_3200AA", {3200, 4, 22, 22, 22, 52, 74, 24, 12, 16, 4, 8, -1, -1, 4, 12, -1, -1, -1, 2, 625}},
        {"DDR4_3200AC", {3200, 4, 24, 24, 24, 52, 76, 24, 12, 16, 4, 8, -1, -1, 4, 12, -1, -1, -1, 2, 625}},
    };

    // organization
    const int m_internel_prefetch_size = 8;
    inline static IndexedVector<string> m_levels = {
        "channel",
        "rank",
        "bankgroup",
        "bank",
        "row",
        "column",
    };
    // commands
    inline static vector<string> m_commands = {
        "ACT",         // activate a row
        "PRE", "PREA", // precharge & close (PREA = precharge all)
        "RD", "RDA",   // read & auto-increase read
        "WR", "WRA",   // write & auto-increase write
        "REFab"        // automatic refresh
    };
    // command enable scope
    inline static map<string, string> m_command_scope = {
        {"ACT", "row"},
        {"PRE", "bank"},
        {"PREA", "rank"},
        {"RD", "column"},
        {"RDA", "column"},
        {"WR", "column"},
        {"WRA", "column"},
        {"REFab", "rank"}};
    // command metadata
    inline static map<string, DRAMCommandMeta> m_command_md = {
        // command  ?open  ?close  ?access ?refresh
        {"ACT", {true, false, false, false}},
        {"PRE", {false, true, false, false}},
        {"PREA", {false, true, false, false}},
        {"RD", {false, false, true, false}},
        {"WR", {false, false, true, false}},
        {"RDA", {false, true, true, false}},
        {"WRA", {false, true, true, false}},
        {"REFab", {false, false, false, true}}};
    // request
    inline static vector<string> m_requests = {
        "read", "write", "all-bank-refresh"};
    // request to command
    inline static map<string, string> m_req2comd = {
        {"read", "RD"},
        {"write", "WR"},
        {"all-bank-refresh", "REFab"}};
    // timing !!
    /**
     * @brief block cycle latency
     * rate
     *
     */
    inline static vector<string> m_timings = {
        "rate",
        "nBL", "nCL", "nRCD", "nRP", "nRAS", "nRC", "nWR", "nRTP", "nCWL",
        "nCCDS", "nCCDL",
        "nRRDS", "nRRDL",
        "nWTRS", "nWTRL",
        "nFAW",
        "nRFC", "nREFI",
        "nCS",
        "tCK_ps"};
    // node states
    inline static vector<string> m_states = {
        "Opened",
        "Closed",
        "PowerUp",
        "N/A"};
    // node init states
    inline static map<string, string> m_init_states = {
        {"channel", m_states[0]},
        {"rank", m_states[2]},
        {"bank_group", m_states[3]},
        {"bank", m_states[1]},
        {"row", m_states[1]},
        {"column", m_states[3]}};

    struct Node
    {
      DDR4 *dram;
      Node *parent;
      int level;
      int id;
      Node(DDR4 *dram, Node *node, int level, int id)
      {
        dram = dram;
        parent = node;
        level = level;
        id = id;
      };
    };

  public:
    vector<Node *> m_channels;
    void init(){
      set_organization();
      set_time_consumption();
    }
   
  private:
   void set_organization(){};
   void set_time_consumption(){};
  // create node and init
    void node_init()
    {
      string target_spec = "";
      auto it = spec_preset.find(target_spec);
      if (it != spec_preset.end())
      {
        specification spec = it->second;
        int n_channels = spec.count[m_levels.indexOf("channel")];
        for (int i = 0; i < n_channels; i++)
        {
          Node *ch = new Node(this, nullptr, 0, i);
          m_channels.push_back(ch);
        }
      }
    }
  };

}