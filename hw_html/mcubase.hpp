#ifndef MCUBASE_HPP
#define MCUBASE_HPP

#include <stdint.h>
#include <string>

class mcubase
{
public:
    mcubase(const std::string &name, const std::string &access);
    const std::string &getaccess() const;
    const std::string &getname() const;

protected:
    ~mcubase() = default;
    const std::string access, name;
};

#endif /* MCUBASE_HPP */
