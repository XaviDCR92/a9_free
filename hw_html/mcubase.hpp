#ifndef MCUBASE_HPP
#define MCUBASE_HPP

#include <stdint.h>
#include <string>

class mcubase
{
public:
    enum access {UNDEF, C, R, S, W, RC, RS, RW, RSV, W1C, W1S};
    mcubase(const std::string &name, const std::string &access);

protected:
    mcubase() = default;
    const std::string &name;
    const access acc;
    uint32_t rst;

private:
    static access get(const std::string &access);
};

#endif /* MCUBASE_HPP */
