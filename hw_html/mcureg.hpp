#ifndef MCUREG_HPP
#define MCUREG_HPP

#include <mcubase.hpp>
#include <bit.hpp>
#include <list>
#include <string>

class mcureg : public mcubase
{
public:
    mcureg(const std::string &name, const std::string &access);
    virtual ~mcureg() = default;
    void add(const bit &);

protected:
    std::list<bit> bits;
};

#endif /* MCUREG_HPP */
