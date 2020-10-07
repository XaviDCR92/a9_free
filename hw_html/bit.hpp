#ifndef BIT_HPP
#define BIT_HPP

#include <mcubase.hpp>
#include <string>

class bit : public mcubase
{
public:
    bit(const std::string &name, const std::string &access,
        const std::string &pos, const std::string &reset,
        const std::string &comment);
    virtual ~bit() = default;
    const std::string &getpos() const;
    const std::string &getreset() const;
    const std::string &getcomment() const;

protected:
    const std::string pos, reset, comment;
};

#endif /* BIT_HPP */
