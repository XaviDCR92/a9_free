#include "mcubase.hpp"
#include <string>
#include <stdint.h>

mcubase::mcubase(const std::string &name, const std::string &access) :
    access(access),
    name(name)
{
}

const std::string &mcubase::getaccess() const
{
    return access;
}

const std::string &mcubase::getname() const
{
    return name;
}
