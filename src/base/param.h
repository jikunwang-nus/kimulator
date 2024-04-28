// #include "yaml-cpp/yaml.h"
#include <map>
using namespace std;
namespace Kimulator
{
    class ValueNode
    {
        string content;

    public:
        int asInt()
        {
            return stoi(content);
        }
    };
    class Params
    {
        string key;
        ValueNode value;
    };
     class ParamHelper
    {
        std::map<std::string, std::string> group(std::string name);
        std::string param(std::string);
    };
}