#ifndef KIMULATOR_BASE_FACTORY_H
#define KIMULATOR_BASE_FACTORY_H
#include "yaml-cpp/yaml.h"
#include <string>
namespace Kimulator
{
#define REGISTER_INTERFACE(_ifce_class, _name, _desc)    \
public:                                                  \
    virtual ~_ifce_class() = default;                    \
    Implementation *m_impl = nullptr;                    \
    static std::string get_name() { return _name; };     \
    static std::string get_desc() { return _desc; };     \
                                                         \
protected:                                               \
    inline static const std::string m_ifce_name = _name; \
    inline static const std::string m_ifce_desc = _desc; \
    static inline bool registered = Factory::register_interface(_name, _desc);
/**
 * @brief     Macro for registering an implementation class to the factory.
 *
 */
#define REGISTER_IMPLEMENTATION(_ifce_class, _impl_class, _name, _desc)                                                                      \
public:                                                                                                                                      \
    inline static const std::string m_ifce_name = _ifce_class::get_name();                                                                   \
    inline static const std::string m_name = _name;                                                                                          \
    inline static const std::string m_desc = _desc;                                                                                          \
                                                                                                                                             \
protected:                                                                                                                                   \
    std::string get_name() const override { return _name; };                                                                                 \
    std::string get_desc() const override { return _desc; };                                                                                 \
    std::string get_ifce_name() const override { return _ifce_class::get_name(); };                                                          \
    _impl_class(const YAML::Node &config, Implementation *parent) : Implementation(config, _ifce_class::get_name(), _name, _desc, parent)    \
    {                                                                                                                                        \
        _ifce_class::m_impl = this;                                                                                                          \
        m_params.set_impl_name(_name);                                                                                                       \
        init();                                                                                                                              \
    };                                                                                                                                       \
    static Implementation *make_##_impl_class(const YAML::Node &config, Implementation *parent) { return new _impl_class(config, parent); }; \
    static inline bool registered = Factory::register_implementation(_ifce_class::get_name(), _name, _desc, make_##_impl_class);

    // state here for static function call
    class IMemorySystem;
    class Factory
    {
        class ImplementationMeta
        {
        public:
            string name;
            string desc;
            Constructor_t constructor;
        };
        class InterfaceMeta
        {
        public:
            string name;
            string desc;
            std::unordered_map<string, ImplementationMeta> impls;
        };
        using Constructor_t = std::function<Implementation *(const YAML::Node &, Implementation *)>;

    public:
        std::unordered_map<string, InterfaceMeta> register_pool;
        static void register_interface(string name, string desc);
        static void register_impl(string ifc_name, string name, string desc, Constructor_t &constructor);
        static IMemorySystem *create_memory_system(const YAML::Node &config);
        static Instantiation *create_instance(string name, YAML::Node &config);
    };
}
#endif