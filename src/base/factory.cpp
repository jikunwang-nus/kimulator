#include "base/factory.h"
#include "base/exception.h"
namespace Kimulator
{
    void Factory::register_interface(string name, string desc)
    {
        if (register_pool.find(name) != register_pool.end())
        {
            register_pool[name] = {name, desc};
        }
    };
    InterfaceMeta *search_interface(string name)
    {
        if (auto at = register_pool.find(name); at != register_pool.end())
        {
            return at;
        }
        return nullptr;
    };
    void Factory::register_impl(string ifc_name, string name, string desc, Constructor_t &constructor)
    {
        // check if interface legal
        auto ifc = register_pool.find(ifc_name);
        if (ifc == register_pool.end())
        {
            throw ConfigurationError("interface does not exsits");
        }
        // check if impl already added
        InterfaceMeta &ifc_info = ifc->second;
        if (auto at = ifc_info.impls.find(name); at != ifc_info.impls.end())
        {
            throw ConfigurationError("impl already exsits");
        }
        ifc_info.impls[name] = {name, desc, constructor};
    };
    Instantiation *Factory::create_instance(string name, YAML::Node &config)
    {
        // check
        string name = "MemorySystem";
        // @todo read from config
        string impl_name = "generic";
        // search from factory registry
        InterfaceMeta *ifc_info = search_interface(name);
        if (auto at = ifc_info->impls.find(impl_name); at != ifc_info->impls.end())
        {
            ImplementationMeta &impl = at->second;
            Constructor_t cons = impl.constructor;
            return cons(config)
        }
    }
    IMemorySystem *Factory::create_memory_system(YAML::Node &config)
    {
        Instantiation *instance = create_instance(IMemorySystem::get_name(), config);
        // convert to memory system
        IMemorySystem *memory_system = dynamic_cast<IMemorySystem *>(instance);
        if (memory_system == nullptr)
        {
            throw ConfigurationError("memory create failed!");
        }
        return memory_system;
    }
}