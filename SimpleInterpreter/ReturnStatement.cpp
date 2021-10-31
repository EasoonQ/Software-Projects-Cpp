#include "ReturnStatement.h"
ReturnStatement::ReturnStatement(int linenum) { m_linenum = linenum; }
ReturnStatement::~ReturnStatement() {}

void ReturnStatement::execute(ProgramState* state, std::ostream& outf) {
    if (!state->emptyRe()) {              // check if the stack is empty
        state->setLines(state->getRe());  // return to the next line of last GOSUB
    } else {
        exit(0);
    }
}