#include "mcubase.hpp"
#include <string>
#include <stdint.h>

mcubase::mcubase(const std::string &name, const std::string &access) :
    name(name),
    acc(get(access)),
    rst(0)
{
}

mcubase::access mcubase::get(const std::string &access)
{
    if (access == "rsv")
        return mcubase::RSV;
    else if (access == "w1c")
        return mcubase::W1C;
    else if (access == "w1s")
        return mcubase::W1S;
    else if (access == "rc")
        return mcubase::RC;
    else if (access == "rs")
        return mcubase::RS;
    else if (access == "rw")
        return mcubase::RW;
    else if (access == "c")
        return mcubase::C;
    else if (access == "s")
        return mcubase::S;
    else if (access == "r")
        return mcubase::R;
    else if (access == "w")
        return mcubase::W;

    return mcubase::UNDEF;
}
