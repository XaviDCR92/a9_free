#include "html.hpp"
#include "mcureg.hpp"
#include "bit.hpp"
#include "instance.hpp"
#include "memory.hpp"
#include "var.hpp"
#include <xmlParser.h>
#include <list>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int addinstances(const XMLNode &root, const std::string &mname, html &html)
{
    int n = 0;
    std::list<instance> instances;

    for (int i = 0; i < root.nChildNode("archive"); i++)
    {
        const XMLNode archive = root.getChildNode("archive", &n);
        int n = 0;

        for (int i = 0; i < archive.nChildNode("instance"); i++)
        {
            const XMLNode inst = archive.getChildNode("instance", &n);
            const char *const name = inst.getAttribute("name");
            const char *const address = inst.getAttribute("address");
            const char *const type = inst.getAttribute("type");

            if (!name || !address || !type)
                continue;
            else if (type == mname)
                instances.push_back(instance(name, address));
        }
    }

    html.add(instances);

    return 0;
}

static std::string getcomments(const XMLNode &node)
{
    std::string comments;
    int n = 0;

    for (int i = 0; i < node.nChildNode("comment"); i++)
    {
        const XMLNode comment = node.getChildNode("comment", &n);
        const char *const cmt = comment.getText();

        if (cmt)
        {
            if (!comments.empty())
                comments += "\n";

            comments += cmt;

            int n = 0;

            // xmlparser cannot process incomplete tags inside children, so
            // the following example would not work as it returns nullptr:
            // <comment> Audio interface.
            // <br /> 0: disabled
            // <br /> 1 = enabled
            // </comment>
            for (int i = 0; i < comment.nChildNode("br"); i++)
            {
                const XMLNode br = comment.getChildNode("br", &n);
                const char *const cmt = br.getText();

                if (cmt)
                {
                    if (!comments.empty())
                        comments += "\n";

                    comments += cmt;
                }
            }
        }
    }

    return comments;
}

static void printvars(const XMLNode &archive, html &html)
{
    int n = 0;
    std::list<var> vars;

    for (int i = 0; i < archive.nChildNode("var"); i++)
    {
        const XMLNode varn = archive.getChildNode("var", &n);
        const char *const name = varn.getAttribute("name");
        const char *const value = varn.getAttribute("value");

        if (!name || !value)
            continue;

        const std::string comments = getcomments(varn);
        vars.push_back(var(name, value, comments));
    }

    html.add(vars);
}

static void printmemories(const XMLNode &node, html &html)
{
    int n = 0;
    std::list<memory> memories;

    for (int i = 0; i < node.nChildNode("memory"); i++)
    {
        const XMLNode mem = node.getChildNode("memory", &n);
        const char *const name = mem.getAttribute("name");
        const char *const size = mem.getAttribute("size");

        if (!name || !size)
            continue;

        memories.push_back(memory(name, size, getcomments(mem)));
    }

    html.add(memories);
}

static int getregs(const XMLNode &root, html &html)
{
    int n = 0;

    for (int i = 0; i < root.nChildNode("archive"); i++)
    {
        const XMLNode archive = root.getChildNode("archive", &n);
        const char *const relative = archive.getAttribute("relative");

        if (!relative)
            continue;

        printvars(archive, html);

        int n = 0;

        for (int i = 0; i < archive.nChildNode("module"); i++)
        {
            const XMLNode module = archive.getChildNode("module", &n);
            const char *const mname = module.getAttribute("name");

            if (!mname)
                continue;

            html.title(mname);
            printvars(module, html);
            addinstances(root, mname, html);

            int n = 0;
            uint32_t offset = 0;

            for (int i = 0; i < module.nChildNode("reg"); i++, offset += sizeof (uint32_t))
            {
                const XMLNode reg = module.getChildNode("reg", &n);
                const char *const name = reg.getAttribute("name");
                const char *const access = reg.getAttribute("protect");

                if (!name || !access)
                    continue;

                mcureg mcureg(name, access, mname, getcomments(reg), offset);

                int n = 0;

                for (int i = 0; i < reg.nChildNode("bits"); i++)
                {
                    const XMLNode bits = reg.getChildNode("bits", &n);
                    const char *const name = bits.getAttribute("name");
                    const char *const access = bits.getAttribute("access");
                    const char *const pos = bits.getAttribute("pos");
                    const char *const rst = bits.getAttribute("rst");

                    if (!name || !access || !pos || !rst)
                        continue;

                    const std::string comments = getcomments(bits);
                    mcureg.add(bit(name, access, pos, rst, comments));
                }

                html.add(mcureg);
            }

            printmemories(module, html);
        }
    }

    return 0;
}

int main(const int argc, const char *const argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "%s <8955_hard.xml-path> <out-path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *const inpath = argv[1];
    const char *const outpath = argv[2];
    html html;

    if (html.open(outpath))
        return EXIT_FAILURE;

    XMLResults res;
    const XMLNode root = XMLNode::parseFile(inpath, "bigarchive", &res);

    if (res.error != eXMLErrorNone)
    {
        fprintf(stderr, "Open %s failed, line %d, column %d, reason: %s.\n",
            inpath, res.nLine, res.nColumn, XMLNode::getError(res.error));
        return EXIT_FAILURE;
    }

    if (getregs(root, html))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
