#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED
#include "Statement.h"
#include <iostream>

class IfStatement : public Statement {
private:
    std::string m_variable;
    std::string m_operation;
    int m_val;
    int m_linenum;

public:
    IfStatement(std::string variable, std::string operation, int val, int linenum);
    virtual ~IfStatement();
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif