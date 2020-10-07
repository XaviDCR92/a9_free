#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <mcubase.hpp>
#include <string>

class instance
{
public:
    instance(const std::string &name, const std::string &address);
    virtual ~instance() = default;
    const std::string &getname() const;
    const std::string &getaddr() const;

protected:
    const std::string name, address;
};

#endif /* INSTANCE_HPP */
