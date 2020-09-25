#include "html.hpp"
#include "mcureg.hpp"
#include "bit.hpp"
#include <xmlParser.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

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
    XMLNode root = XMLNode::parseFile(inpath, "bigarchive", &res);

    if (res.error != eXMLErrorNone)
    {
        fprintf(stderr, "Open %s failed, line %d, column %d, reason: %s.\n",
            inpath, res.nLine, res.nColumn, XMLNode::getError(res.error));
        return EXIT_FAILURE;
    }

    int n = 0;

    for (int i = 0; i < root.nChildNode("archive"); i++)
    {
        const XMLNode archive = root.getChildNode("archive", &n);
        const char *const relative = archive.getAttribute("relative");

        if (!relative)
            continue;

        int n = 0;

        for (int i = 0; i < archive.nChildNode("module"); i++)
        {
            const XMLNode module = archive.getChildNode("module", &n);
            const char *const name = module.getAttribute("name");

            if (!name)
                continue;

            printf("module %s\n", name);
            int n = 0;

            for (int i = 0; i < module.nChildNode("reg"); i++)
            {
                const XMLNode reg = module.getChildNode("reg", &n);
                const char *const name = reg.getAttribute("name");
                const char *const access = reg.getAttribute("protect");

                if (!name || !access)
                    continue;

                printf("\treg %s\n", name);
                mcureg mcureg(name, access);

                int n = 0;

                for (int i = 0; i < reg.nChildNode("bits"); i++)
                {
                    const XMLNode bits = reg.getChildNode("bits", &n);
                    const char *const name = bits.getAttribute("name");
                    const char *const access = bits.getAttribute("access");
                    const char *const pos = bits.getAttribute("pos");
                    const char *const rst = bits.getAttribute("rst");

                    printf("\t\tbit=%s, access=%s, pos=%s, rst=%s\n",
                        name, access, pos, rst);

                    if (!name || !access || !pos || !rst)
                        continue;

                    mcureg.add(bit(name, access, pos));
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
