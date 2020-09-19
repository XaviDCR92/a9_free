#include <ctml.hpp>
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

protected:
    FILE *f;
};
