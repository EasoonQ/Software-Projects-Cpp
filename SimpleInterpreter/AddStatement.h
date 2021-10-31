#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class AddStatement : public Statement {

private:
    std::string m_name;
    std::string m_add;

public:
    // the constructor will first take in "add" as a string
    // then determine if it is a string or an integer
    // and do operations accordingly
    AddStatement(std::string name, std::string add);
    virtual ~AddStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
