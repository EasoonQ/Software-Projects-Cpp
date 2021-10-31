#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class SubStatement : public Statement {
private:
    std::string m_name;
    std::string m_sub;

public:
    // the constructor will first take in "sub" as a string
    // then determine if it is a string or an integer
    // and do operations accordingly
    SubStatement(std::string name, std::string sub);
    virtual ~SubStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif