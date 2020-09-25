#include <bit.hpp>
#include <iostream>

bit::bit(const std::string &name, const std::string &access,
    const std::string &pos) :
    mcubase(name, access),
    off(get(pos))
{
}

struct bit::off bit::get(const std::string &pos)
{
    struct off off = {0};
    std::cout << pos + "\n";
    return off;
}
