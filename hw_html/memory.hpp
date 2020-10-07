#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>

class memory
{
public:
    memory(const std::string &name, const std::string &size,
        const std::string &comment);
    virtual ~memory() = default;
    const std::string name, size, comment;
};

#endif /* MEMORY_HPP */
