#ifndef KIMULATOR_BASE_EXCEPTION
#define KIMULATOR_BASE_EXCEPTION
#include <stdexcept>
#include <format>
#include <iostream>
#include <string>

namespace Kimulator
{
    struct ConfigurationError : public std::runtime_error
    {
        ConfigurationError(const std::string &message) : std::runtime_error(message) {}
    };
}
#endif