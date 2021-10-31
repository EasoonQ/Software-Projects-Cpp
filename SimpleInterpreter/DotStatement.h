#ifndef DOT_STATEMENT_INCLUDED
#define DOT_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class DotStatement : public Statement {

public:
    DotStatement();
    virtual ~DotStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif