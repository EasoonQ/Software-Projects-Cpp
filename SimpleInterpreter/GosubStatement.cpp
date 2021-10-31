#include "GosubStatement.h"
GosubStatement::GosubStatement(int linenum) { m_linenum = linenum; }
GosubStatement::~GosubStatement() {}

void GosubStatement::execute(ProgramState* state, std::ostream& outf) {
    state->setRe(state->getLines() + 1);  // push the next line on stack
    state->setLines(m_linenum);           // jump to the target line
}
