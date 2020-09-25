#ifndef HTML_HPP
#define HTML_HPP

#include <ctml.hpp>
#include <mcubase.hpp>
#include <stdio.h>

class html
{
public:
    enum error
    {
        OK,
        INVALID_PATH,
        OPEN_ERR,
        WRITE_ERR
    };

    html();
    virtual ~html();
    error open(const char *path);
    error add(const mcubase &reg);

protected:
    FILE *f;
};

#endif /* HTML_HPP */
