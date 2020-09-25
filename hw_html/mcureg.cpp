#include <mcureg.hpp>
#include <mcubase.hpp>
#include <bit.hpp>
#include <list>
#include <string>

mcureg::mcureg(const std::string &name, const std::string &access) :
    mcubase(name, access)
{
}

void mcureg::add(const bit &bit)
{
    bits.push_back(bit);
}
