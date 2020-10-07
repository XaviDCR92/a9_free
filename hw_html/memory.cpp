#include <memory.hpp>
#include <string>

memory::memory(const std::string &name, const std::string &size,
    const std::string &comment) :
    name(name),
    size(size),
    comment(comment)
{
}
