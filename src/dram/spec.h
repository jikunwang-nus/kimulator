#ifndef KIMULATOR_DRAM_SPEC_H
#define KIMULATOR_DRAM_SPEC_H
#include <vector>
#include <array>
#include <map>
#include "../base/exception.h"
using namespace std;
namespace Kimulator
{

  // define density, dq and organization
  struct specification
  {
    int density;       // capacity of each module
    int dq;            // number of data queue
    vector<int> count; // for DDR4, they are channels, ranks, bank groups, bank, rows, columns
  };
  struct DRAMCommandMeta
  {
    bool is_opening = false;
    bool is_closing = false;
    bool is_accessing = false;
    bool is_refreshing = false;
  };
  template <typename K>
  class KVector : public std::vector<K>
  {
  public:
    KVector(std::initializer_list<K> initList) : std::vector<K>(initList) {}
    int indexOf(K value)
    {
      auto at = std::find(this->begin(), this->end(), value);
      if (at != this->end())
      {
        return std::distance(this->begin(), at);
      }
      else
        return -1;
    }
  };
  struct TimingConsInitializer {
  std::string_view level;
  std::vector<std::string_view> preceding;
  std::vector<std::string_view> following;
  int latency = -1;
  int window = 1;
  bool is_sibling = false;
};
struct TimingConsEntry {
  /// The command that the timing constraint is constraining.
  int cmd;
  /// The value of the timing constraint (in number of cycles).
  int val;
  /// How long of a history to keep track of?
  int window = 1;
  /// Whether this timing constraint is affecting siblings in the same level.
  bool sibling = false;

  TimingConsEntry(int cmd, int val, int window = 1, bool sibling = false):
  cmd(cmd), val(val), window(window), sibling(sibling) {
    if (this->window < 0) {
      this->window = 0;
    }
  };
};
  template<class T>
void populate_timingcons(T* spec, std::vector<TimingConsInitializer> initializer) {
  spec->m_timing_cons.resize(T::m_levels.size(), std::vector<std::vector<TimingConsEntry>>(T::m_commands.size()));
  for (const auto& ts : initializer) {
    int level = T::m_levels(ts.level);  // cannot be consteval...
    for (auto p_cmd_str : ts.preceding) {
      int p_cmd = T::m_commands(p_cmd_str);
      for (auto f_cmd_str : ts.following) {
        int f_cmd = T::m_commands(f_cmd_str);
        spec->m_timing_cons[level][p_cmd].push_back({f_cmd, ts.latency, ts.window, ts.is_sibling});
      }
    }
  }
};
  template <typename K, typename V>
  class Kcontainer
  {
  private:
    vector<K> _keys;
    map<K, V> kvm;

  public:
    Kcontainer(vector<K> ds)
    {
      _keys = ds;
    }
    vector<K> keys()
    {
      return _keys;
    }
    V value(string key)
    {
      return kvm[key];
    }
    void setVal(string key, V value)
    {
      kvm[key] = value;
    }
    void setValues(vector<V> vals)
    {
      // check if length equals
      if (vals.size() != _keys.size())
      {
        throw ConfigurationError("length does not match!");
      }
      for (size_t i = 0; i < _keys.size(); i++)
      {
        kvm[_keys[i]] = vals[i];
      }
    }
    int indexOf(K value)
    {
      auto at = std::find(_keys->begin(), _keys->end(), value);
      if (at != _keys->end())
      {
        return std::distance(_keys->begin(), at);
      }
      else
        return -1;
    }
  };
}
#endif