#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class MultStatement : public Statement {

private:
    std::string m_name;
    std::string m_mult;

public:
    // the constructor will first take in "mult" as a string
    // then determine if it is a string or an integer
    // and do operations accordingly
    MultStatement(std::string name, std::string mult);
    virtual ~MultStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif