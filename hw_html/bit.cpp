#include <bit.hpp>
#include <iostream>

bit::bit(const std::string &name, const std::string &access,
    const std::string &pos, const std::string &reset,
    const std::string &comment) :
    mcubase(name, access),
    pos(pos),
    reset(reset),
    comment(comment)
{
}

const std::string &bit::getpos() const
{
    return pos;
}

const std::string &bit::getreset() const
{
    return reset;
}

const std::string &bit::getcomment() const
{
    return comment;
}
