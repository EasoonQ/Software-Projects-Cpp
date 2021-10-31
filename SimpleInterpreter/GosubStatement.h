#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class GosubStatement : public Statement {
private:
    int m_linenum;

public:
    GosubStatement(int linenum);
    virtual ~GosubStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif