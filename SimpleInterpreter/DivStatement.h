#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class DivStatement : public Statement {

private:
    std::string m_name;
    std::string m_div;

public:
    // the constructor will first take in "div" as a string
    // then determine if it is a string or an integer
    // and do operations accordingly
    DivStatement(std::string name, std::string div);
    virtual ~DivStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
