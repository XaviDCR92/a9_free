#include "html.hpp"
#include <ctml.hpp>
#include <stdio.h>
#include <string.h>
#include <errno.h>

html::html() :
    f(nullptr)
{
}

html::~html()
{
    if (f)
        fclose(f);
}

html::error html::open(const char *const path)
{
    if (!path)
        return html::INVALID_PATH;

    f = fopen(path, "wb");

    if (!f)
    {
        fprintf(stderr, "could not open %s for writing, reason: %s\n", path,
            strerror(errno));
        return html::OPEN_ERR;
    }

    CTML::Document doc;

    doc.AppendNodeToHead(CTML::Node("TITLE", "A9 register map"));

    if (fprintf(f, "%s\n", doc.ToString().c_str()) < 0)
    {
        fprintf(stderr, "HTML write error\n");
        return html::WRITE_ERR;
    }

    return html::OK;
}
