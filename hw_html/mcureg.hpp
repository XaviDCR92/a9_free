#ifndef MCUREG_HPP
#define MCUREG_HPP

#include <mcubase.hpp>
#include <bit.hpp>
#include <instance.hpp>
#include <stdint.h>
#include <list>
#include <string>
#include <stdio.h>

class mcureg : public mcubase
{
public:
    mcureg(const std::string &name, const std::string &access,
        const std::string &periph, const std::string &comment, uint32_t pos);
    virtual ~mcureg() = default;
    void add(const bit &);
    void add(const instance &);
    const std::list<bit> &getbits() const;
    const std::list<instance> &getinstances() const;
    const std::string periph;
    const std::string comment;
    const uint32_t pos;

protected:
    std::list<bit> bits;
    std::list<instance> instances;
};

#endif /* MCUREG_HPP */
