#include <html.hpp>
#include <mcubase.hpp>
#include <ctml.hpp>
#include <iterator>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <list>

html::html() :
    f(nullptr)
{
}

html::~html()
{
    doc.AppendNodeToBody(body);

    if (f)
    {
        const struct CTML::ToStringOptions tso =
        {
            CTML::StringFormatting::MULTIPLE_LINES
        };

        if (fprintf(f, "%s\n", doc.ToString(tso).c_str()) < 0)
            std::cerr << "HTML write error" << std::endl;

        fclose(f);
    }
}

int html::open(const char *const path)
{
    if (!path)
    {
        errno = EINVAL;
        return -1;
    }

    f = fopen(path, "wb");

    if (!f)
    {
        fprintf(stderr, "could not open %s for writing, reason: %s\n", path,
            strerror(errno));
        return -1;
    }

    static const std::string title = "A9/RDA8955 register map";
    doc.AppendNodeToHead(CTML::Node("TITLE", title));
    doc.AppendNodeToBody(CTML::Node("h1", title));
    doc.AppendNodeToBody(CTML::Node("h2", "Peripheral list"));
    return 0;
}

void html::add(const std::list<memory> &memories)
{
    if (memories.empty())
        return;

    body.AppendChild(CTML::Node("h3", "Memories list"));
    CTML::Node table("table"), headtr("tr");

    headtr.AppendChild(CTML::Node("th", "Name"));
    headtr.AppendChild(CTML::Node("th", "Size"));
    headtr.AppendChild(CTML::Node("th", "Comments"));
    table.AppendChild(headtr);

    for (auto m : memories)
    {
        CTML::Node tr("tr");

        tr.AppendChild(CTML::Node("td", m.name));
        tr.AppendChild(CTML::Node("td", m.size));
        tr.AppendChild(CTML::Node("td", m.comment));
        table.AppendChild(tr);
    }

    body.AppendChild(table);
}

void html::add(const mcureg &reg)
{
    if (!reg.comment.empty())
    {
        body.AppendChild(CTML::Node("p", reg.comment));
        newline(body);
    }

    if (!reg.getbits().empty())
    {
        CTML::Node table("table"), headtr("tr");

        headtr.AppendChild(CTML::Node("th", "Bit name"));
        headtr.AppendChild(CTML::Node("th", "Position"));
        headtr.AppendChild(CTML::Node("th", "Reset value"));
        headtr.AppendChild(CTML::Node("th", "Read/write access"));
        headtr.AppendChild(CTML::Node("th", "Comments"));
        table.AppendChild(headtr);

        for (auto bit : reg.getbits())
        {
            CTML::Node tr("tr");

            tr.AppendChild(CTML::Node("td", bit.getname()));
            tr.AppendChild(CTML::Node("td", bit.getpos()));
            tr.AppendChild(CTML::Node("td", bit.getreset()));
            tr.AppendChild(CTML::Node("td", bit.getaccess()));
            tr.AppendChild(CTML::Node("td", bit.getcomment().empty() ?
                "-" : bit.getcomment()));
            table.AppendChild(tr);
        }

        CTML::Node rn("h3", reg.getname());
        char offset[16];
        snprintf(offset, sizeof offset, "0x%X", reg.pos);
        rn.AppendText("(offset " + std::string(offset) + ")");
        body.AppendChild(rn);
        CTML::Node ref("a", reg.periph);
        ref.SetAttribute("href", "#" + reg.periph);
        body.AppendChild(ref);
        body.AppendChild(table);
    }
    else
    {
        body.AppendChild(CTML::Node("h3", reg.getname()));
        body.AppendChild(CTML::Node("p", "No bits available"));
    }
}

CTML::Node &html::newline(CTML::Node &n)
{
    n.AppendChild(CTML::Node("br").UseClosingTag(false));
    return n;
}

void html::add(const std::list<var> &vars)
{
    if (vars.empty())
        return;

    body.AppendChild(CTML::Node("h3", "Constant list"));
    CTML::Node table("table"), headtr("tr");

    headtr.AppendChild(CTML::Node("th", "Name"));
    headtr.AppendChild(CTML::Node("th", "Value"));
    headtr.AppendChild(CTML::Node("th", "Comments"));
    table.AppendChild(headtr);

    for (auto var : vars)
    {
        CTML::Node tr("tr");

        tr.AppendChild(CTML::Node("td", var.getname()));
        tr.AppendChild(CTML::Node("td", var.getvalue()));
        tr.AppendChild(CTML::Node("td", var.getcomment().empty() ?
            "-" : var.getcomment()));
        table.AppendChild(tr);
    }

    body.AppendChild(table);
}

void html::title(const std::string &title)
{
    newline(body);
    doc.AppendNodeToBody(newline(CTML::Node("a", title)
        .SetAttribute("href", "#" + title)));
    titlebody(title);
}

void html::titlebody(const std::string &title)
{
    CTML::Node font("font");
    font.SetAttribute("size", "+2");
    font.AppendText(title);
    CTML::Node n("a");
    n.SetAttribute("name", title);
    newline(n);
    font.AppendChild(n);
    body.AppendChild(font);
}

void html::add(const std::list<instance> &instances)
{
    if (instances.empty())
        return;

    body.AppendChild(CTML::Node("h3", "Instance list"));
    CTML::Node table("table"), headtr("tr");

    headtr.AppendChild(CTML::Node("th", "Name"));
    headtr.AppendChild(CTML::Node("th", "Address"));
    table.AppendChild(headtr);

    for (auto i : instances)
    {
        CTML::Node tr("tr");

        tr.AppendChild(CTML::Node("td", i.getname()));
        tr.AppendChild(CTML::Node("td", i.getaddr()));
        table.AppendChild(tr);
    }

    body.AppendChild(table);
}
