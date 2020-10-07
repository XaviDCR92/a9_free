#include <instance.hpp>
#include <mcubase.hpp>
#include <string>

instance::instance(const std::string &name, const std::string &address) :
    name(name),
    address(address)
{
}

const std::string &instance::getname() const
{
    return name;
}

const std::string &instance::getaddr() const
{
    return address;
}
