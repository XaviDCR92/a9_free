#ifndef BIT_HPP
#define BIT_HPP

#include <mcubase.hpp>
#include <string>

class bit : public mcubase
{
public:
    bit(const std::string &name, const std::string &access,
        const std::string &pos);
    virtual ~bit() = default;

protected:
    const struct off {unsigned int upper, lower;} off;
    static struct off get(const std::string &pos);
    std::string comment;
};

#endif /* BIT_HPP */
