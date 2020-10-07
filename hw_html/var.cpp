#include "var.hpp"
#include <list>
#include <string>
#include <stdint.h>

var::var(const std::string &name, const std::string &value,
    const std::string &comment) :
    name(name),
    value(value),
    comment(comment)
{
}

const std::string &var::getvalue() const
{
    return value;
}

const std::string &var::getname() const
{
    return name;
}

const std::string &var::getcomment() const
{
    return comment;
}
