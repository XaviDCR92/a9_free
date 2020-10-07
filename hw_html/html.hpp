#ifndef HTML_HPP
#define HTML_HPP

#include <ctml.hpp>
#include <mcureg.hpp>
#include <instance.hpp>
#include <var.hpp>
#include <memory.hpp>
#include <list>
#include <string>
#include <stdio.h>

class html
{
public:
    html();
    virtual ~html();
    int open(const char *path);
    void add(const mcureg &reg);
    void add(const std::list<var> &vars);
    void add(const std::list<instance> &instances);
    void add(const std::list<memory> &memories);
    void title(const std::string &title);
    void titlebody(const std::string &title);

protected:
    CTML::Node &newline(CTML::Node &n);
    FILE *f;
    CTML::Document doc;
    CTML::Node body;
};

#endif /* HTML_HPP */
