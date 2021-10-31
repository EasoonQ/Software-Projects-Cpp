#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class GotoStatement : public Statement {
private:
    int m_value;

public:
    GotoStatement(int value);
    virtual ~GotoStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif