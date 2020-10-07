#include <mcureg.hpp>
#include <mcubase.hpp>
#include <bit.hpp>
#include <list>
#include <string>
#include <iostream>
#include <stdio.h>

mcureg::mcureg(const std::string &name, const std::string &access,
    const std::string &periph, const std::string &comment, const uint32_t pos) :
    mcubase(name, access),
    periph(periph),
    comment(comment),
    pos(pos)
{
}

void mcureg::add(const bit &bit)
{
    bits.push_back(bit);
}

void mcureg::add(const instance &instance)
{
    instances.push_back(instance);
}

const std::list<bit> &mcureg::getbits() const
{
    return bits;
}

const std::list<instance> &mcureg::getinstances() const
{
    return instances;
}
