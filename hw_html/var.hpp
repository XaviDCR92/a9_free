#ifndef VAR_HPP
#define VAR_HPP

#include <stdint.h>
#include <string>

class var
{
public:
    var(const std::string &name, const std::string &value,
        const std::string &comment);
    const std::string &getname() const;
    const std::string &getvalue() const;
    const std::string &getcomment() const;

protected:
    var() = default;
    const std::string name, value, comment;
};

#endif /* VAR_HPP */
