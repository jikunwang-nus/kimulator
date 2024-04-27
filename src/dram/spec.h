#include <vector>
#include <array>
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
  template <typename T>
  class IndexedVector : public vector<T>
  {
  public:
    using std::vector<T>::vector;
    int indexOf(T value)
    {
      auto at = std::find(this->begin, this->end, value);
      if (at != this->end)
      {
        return std::distance(this->begin, at);
      }
      else
        return -1;
    }
  };
}