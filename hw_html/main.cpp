#include "html.hpp"
#include "mcureg.hpp"
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

                if (!name)
                    continue;

                printf("\treg %s\n", name);

                int n = 0;

                for (int i = 0; i < reg.nChildNode("bits"); i++)
                {
                    const XMLNode bits = reg.getChildNode("bits", &n);
                    const char *const name = bits.getAttribute("name");
                    mcureg::access access = mcureg::UNDEF;
                    const char *const access_cs = bits.getAttribute("access");

                    if (!access_cs)
                        continue;

                    const std::string access_s = access_cs;

                    if (access_s == "rsv")
                        access = mcureg::RSV;
                    else if (access_s == "w1c")
                        access = mcureg::W1C;
                    else if (access_s == "w1s")
                        access = mcureg::W1S;
                    else if (access_s == "rc")
                        access = mcureg::RC;
                    else if (access_s == "rs")
                        access = mcureg::RS;
                    else if (access_s == "rw")
                        access = mcureg::RW;
                    else if (access_s == "c")
                        access = mcureg::C;
                    else if (access_s == "s")
                        access = mcureg::S;
                    else if (access_s == "r")
                        access = mcureg::R;
                    else if (access_s == "w")
                        access = mcureg::W;

                    if (access == mcureg::UNDEF)
                        fprintf(stderr, "%s: undefined access\n", name);
                    else
                    {
                        printf("\t\t%s, access %s\n", name, access_cs);
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
