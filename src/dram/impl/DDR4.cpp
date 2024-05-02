#include "base/utils.h"
#include "dram/dram.h"
#include "dram/lambdas.h"
#include "dram/node.h"
namespace Kimulator
{

  class DDR4 : public IDRAM
  {

  public:
    // hierachy for each spec
    inline static const std::map<std::string, Organization> spec_preset = {
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
    inline static KVector<string> m_levels = {
        "channel",
        "rank",
        "bankgroup",
        "bank",
        "row",
        "column",
    };
    // commands
    inline static KVector<std::string> m_commands = {
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
    inline static KVector<string> m_states = {
        "Opened",
        "Closed",
        "PowerUp",
        "N/A"};
    // node init states
    inline static map<string, string> m_init_states = {
        {"channel", "Opened"},
        {"rank", "PowerUp"},
        {"bank_group", "N/A"},
        {"bank", "Closed"},
        {"row", "Closed"},
        {"column", "N/A"}};

    // inline static map<string, string> m_init_states = {
    //     {"channel", m_states[0]},
    //     {"rank", m_states[2]},
    //     {"bank_group", m_states[3]},
    //     {"bank", m_states[1]},
    //     {"row", m_states[1]},
    //     {"column", m_states[3]}};

    struct Node : public DRAMNodeBase<DDR4>
    {
      DDR4 *dram;
      Node *parent;
      int level;
      int id;
      Node(DDR4 *dram, Node *parent, int level, int id) : DRAMNodeBase<DDR4>(dram, parent, level, id){};
    };

  public:
    vector<Node *> m_channels;

    FuncVV<Func_void<Node>> m_actions;
    FuncVV<Func_int<Node>> m_prerequisites;
    FuncVV<Func_bool<Node>> m_rowhits;
    FuncVV<Func_bool<Node>> m_rowopens;
    void init()
    {
      set_organization();
      set_time_consumption();
      set_actions();
      set_prerequisites();
      set_rowhits();
      set_rowopens();
      node_init();
    }

  private:
    // set organization of dram basen on configuration
    void set_organization()
    {
      // set all vars in spec
      // @todo retrieve param from config
      string preset = "DDR4_8Gb_x8";
      int channels = 1;
      int rank = 2;
      m_channel_width = 64;
      m_organization.count.resize(m_levels.size());

      m_organization = spec_preset.at(preset);
    };
    // set and calculate time consumptation based on configuration
    void set_time_consumption()
    {
      // check size
      m_timings_ct.keys().resize(m_timings.size());
      // set timing value from provided map
      string timing_name = "DDR4_2400R";
      auto at = timing_presets.find(timing_name);
      if (at != timing_presets.end())
      {
        vector<int> val = at->second;
        m_timings_ct.setValues(val);
      }
      // set tCK
      int tCK_ps = 1E6 / (m_timings_ct.value("rate") / 2);
      m_timings_ct.setVal("tCK_ps", tCK_ps);

      // lambda calculate ids
      int dq_id = [](int dequeue) -> int
      {
        switch (dequeue)
        {
        case 4:
          return 0;
        case 8:
          return 1;
        case 16:
          return 2;
        default:
          return -1;
        }
      }(m_organization.dq);
      int rate_id = [](int rate) -> int
      {
        switch (rate)
        {
        case 1600:
          return 0;
        case 1866:
          return 1;
        case 2133:
          return 2;
        case 2400:
          return 3;
        case 2666:
          return 4;
        case 2933:
          return 5;
        case 3200:
          return 6;
        default:
          return -1;
        }
      }(m_timings_ct.value("rate"));
      constexpr int nRRDS_TABLE[3][7] = {
          // 1600  1866  2133  2400  2666  2933  3200
          {4, 4, 4, 4, 4, 4, 4}, // x4
          {4, 4, 4, 4, 4, 4, 4}, // x8
          {5, 5, 6, 7, 8, 8, 9}, // x16
      };
      constexpr int nRRDL_TABLE[3][7] = {
          // 1600  1866  2133  2400  2666  2933  3200
          {5, 5, 6, 6, 7, 8, 8},   // x4
          {5, 5, 6, 6, 7, 8, 8},   // x8
          {6, 6, 7, 8, 9, 10, 11}, // x16
      };
      constexpr int nFAW_TABLE[3][7] = {
          // 1600  1866  2133  2400  2666  2933  3200
          {16, 16, 16, 16, 16, 16, 16}, // x4
          {20, 22, 23, 26, 28, 31, 34}, // x8
          {28, 28, 32, 36, 40, 44, 48}, // x16
      };

      if (dq_id != -1 && rate_id != -1)
      {
        m_timings_ct.setVal("nRRDS", nRRDS_TABLE[dq_id][rate_id]);
        m_timings_ct.setVal("nRRDL", nRRDL_TABLE[dq_id][rate_id]);
        m_timings_ct.setVal("nFAW", nFAW_TABLE[dq_id][rate_id]);
      }
      // Refresh timings
      // tRFC table (unit is nanosecond!)
      constexpr int tRFC_TABLE[3][4] = {
          //  2Gb   4Gb   8Gb  16Gb
          {160, 260, 360, 550}, // Normal refresh (tRFC1)
          {110, 160, 260, 350}, // FGR 2x (tRFC2)
          {90, 110, 160, 260},  // FGR 4x (tRFC4)
      };

      // tREFI(base) table (unit is nanosecond!)
      constexpr int tREFI_BASE = 7800;
      int density_id = [](int density_Mb) -> int
      {
        switch (density_Mb)
        {
        case 2048:
          return 0;
        case 4096:
          return 1;
        case 8192:
          return 2;
        case 16384:
          return 3;
        default:
          return -1;
        }
      }(m_organization.density);
      m_timings_ct.setVal("nRFC", JEDEC_rounding(tRFC_TABLE[0][density_id], tCK_ps));
      m_timings_ct.setVal("nREFI", JEDEC_rounding(tREFI_BASE, tCK_ps));

      // set read latency
      m_read_latency = m_timings_ct.value("nCL") + m_timings_ct.value("nBL");
// Populate the timing constraints
#define V(timing) (m_timings_ct.value(timing))
      populate_timingcons(this, {
                                    /*** Channel ***/
                                    // CAS <-> CAS
                                    /// Data bus occupancy
                                    {.level = "channel", .preceding = {"RD", "RDA"}, .following = {"RD", "RDA"}, .latency = V("nBL")},
                                    {.level = "channel", .preceding = {"WR", "WRA"}, .following = {"WR", "WRA"}, .latency = V("nBL")},

                                    /*** Rank (or different BankGroup) ***/
                                    // CAS <-> CAS
                                    /// nCCDS is the minimal latency for column commands
                                    {.level = "rank", .preceding = {"RD", "RDA"}, .following = {"RD", "RDA"}, .latency = V("nCCDS")},
                                    {.level = "rank", .preceding = {"WR", "WRA"}, .following = {"WR", "WRA"}, .latency = V("nCCDS")},
                                    /// RD <-> WR, Minimum Read to Write, Assuming tWPRE = 1 tCK
                                    {.level = "rank", .preceding = {"RD", "RDA"}, .following = {"WR", "WRA"}, .latency = V("nCL") + V("nBL") + 2 - V("nCWL")},
                                    /// WR <-> RD, Minimum Read after Write
                                    {.level = "rank", .preceding = {"WR", "WRA"}, .following = {"RD", "RDA"}, .latency = V("nCWL") + V("nBL") + V("nWTRS")},
                                    /// CAS <-> CAS between sibling ranks, nCS (rank switching) is needed for new DQS
                                    {.level = "rank", .preceding = {"RD", "RDA"}, .following = {"RD", "RDA", "WR", "WRA"}, .latency = V("nBL") + V("nCS"), .is_sibling = true},
                                    {.level = "rank", .preceding = {"WR", "WRA"}, .following = {"RD", "RDA"}, .latency = V("nCL") + V("nBL") + V("nCS") - V("nCWL"), .is_sibling = true},
                                    /// CAS <-> PREab
                                    {.level = "rank", .preceding = {"RD"}, .following = {"PREA"}, .latency = V("nRTP")},
                                    {.level = "rank", .preceding = {"WR"}, .following = {"PREA"}, .latency = V("nCWL") + V("nBL") + V("nWR")},
                                    /// RAS <-> RAS
                                    {.level = "rank", .preceding = {"ACT"}, .following = {"ACT"}, .latency = V("nRRDS")},
                                    {.level = "rank", .preceding = {"ACT"}, .following = {"ACT"}, .latency = V("nFAW"), .window = 4},
                                    {.level = "rank", .preceding = {"ACT"}, .following = {"PREA"}, .latency = V("nRAS")},
                                    {.level = "rank", .preceding = {"PREA"}, .following = {"ACT"}, .latency = V("nRP")},
                                    /// RAS <-> REF
                                    {.level = "rank", .preceding = {"ACT"}, .following = {"REFab"}, .latency = V("nRC")},
                                    {.level = "rank", .preceding = {"PRE", "PREA"}, .following = {"REFab"}, .latency = V("nRP")},
                                    {.level = "rank", .preceding = {"RDA"}, .following = {"REFab"}, .latency = V("nRP") + V("nRTP")},
                                    {.level = "rank", .preceding = {"WRA"}, .following = {"REFab"}, .latency = V("nCWL") + V("nBL") + V("nWR") + V("nRP")},
                                    {.level = "rank", .preceding = {"REFab"}, .following = {"ACT"}, .latency = V("nRFC")},

                                    /*** Same Bank Group ***/
                                    /// CAS <-> CAS
                                    {.level = "bankgroup", .preceding = {"RD", "RDA"}, .following = {"RD", "RDA"}, .latency = V("nCCDL")},
                                    {.level = "bankgroup", .preceding = {"WR", "WRA"}, .following = {"WR", "WRA"}, .latency = V("nCCDL")},
                                    {.level = "bankgroup", .preceding = {"WR", "WRA"}, .following = {"RD", "RDA"}, .latency = V("nCWL") + V("nBL") + V("nWTRL")},
                                    /// RAS <-> RAS
                                    {.level = "bankgroup", .preceding = {"ACT"}, .following = {"ACT"}, .latency = V("nRRDL")},

                                    /*** Bank ***/
                                    {.level = "bank", .preceding = {"ACT"}, .following = {"ACT"}, .latency = V("nRC")},
                                    {.level = "bank", .preceding = {"ACT"}, .following = {"RD", "RDA", "WR", "WRA"}, .latency = V("nRCD")},
                                    {.level = "bank", .preceding = {"ACT"}, .following = {"PRE"}, .latency = V("nRAS")},
                                    {.level = "bank", .preceding = {"PRE"}, .following = {"ACT"}, .latency = V("nRP")},
                                    {.level = "bank", .preceding = {"RD"}, .following = {"PRE"}, .latency = V("nRTP")},
                                    {.level = "bank", .preceding = {"WR"}, .following = {"PRE"}, .latency = V("nCWL") + V("nBL") + V("nWR")},
                                    {.level = "bank", .preceding = {"RDA"}, .following = {"ACT"}, .latency = V("nRTP") + V("nRP")},
                                    {.level = "bank", .preceding = {"WRA"}, .following = {"ACT"}, .latency = V("nCWL") + V("nBL") + V("nWR") + V("nRP")},
                                });
#undef V
    }
    // set action for rank & bank
    void set_actions()
    {
      // action for rank
      m_actions[m_levels["rank"]][m_commands["PREA"]] = Kimulator::Lambdas::Action::Rank::PREab<DDR4>;
      // action for bank
      m_actions[m_levels["bank"]][m_commands["ACT"]] = Kimulator::Lambdas::Action::Bank::act<DDR4>;
      m_actions[m_levels["bank"]][m_commands["PRE"]] = Kimulator::Lambdas::Action::Bank::pre<DDR4>;
      m_actions[m_levels["bank"]][m_commands["RDA"]] = Kimulator::Lambdas::Action::Bank::pre<DDR4>;
      m_actions[m_levels["bank"]][m_commands["WRA"]] = Kimulator::Lambdas::Action::Bank::pre<DDR4>;
    }
    // set prerequisite for action
    void set_prerequisites()
    {
      // prerequisite for rank action
      m_prerequisites[m_levels["rank"]][m_commands["REFab"]] = Lambdas::Preq::Bank::RequireBankClosed<DDR4>;

      // prerequisite for bank action
      m_prerequisites[m_levels["bank"]][m_commands["RD"]] = Lambdas::Preq::Bank::RequireRowOpen<DDR4>;
      m_prerequisites[m_levels["bank"]][m_commands["WR"]] = Lambdas::Preq::Bank::RequireRowOpen<DDR4>;
    }
    // set rowopen-related
    void set_rowopens()
    {
      // set function to check whether read & write avaliable -> true / false
      m_rowopens[m_levels["bank"]][m_commands["RD"]] = Lambdas::RowOpen::Bank::RDWR<DDR4>;
      m_rowopens[m_levels["bank"]][m_commands["WR"]] = Lambdas::RowOpen::Bank::RDWR<DDR4>;
    }
    // set rowhit-related
    void set_rowhits()
    {
      // set function to check whether read & write avaliable -> true / false
      m_rowhits[m_levels["bank"]][m_commands["RD"]] = Lambdas::RowHit::Bank::RDWR<DDR4>;
      m_rowhits[m_levels["bank"]][m_commands["WR"]] = Lambdas::RowHit::Bank::RDWR<DDR4>;
    }
    // create node and init
    void node_init()
    {
      int n_channels = m_organization.count[m_levels.indexOf("channel")];
      for (int i = 0; i < n_channels; i++)
      {
        Node *ch = new Node(this, nullptr, 0, i);
        m_channels.push_back(ch);
      }
    }
  };
}