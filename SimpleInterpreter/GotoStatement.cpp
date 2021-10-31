#include "GotoStatement.h"
GotoStatement::GotoStatement(int value) { m_value = value; }
GotoStatement::~GotoStatement() {}

void GotoStatement::execute(ProgramState* state, std::ostream& outf) {
    // throw exception if the target line is out of range
    if ((m_value < 1) || (m_value > state->getMaxNumLine())) {
        throw std::invalid_argument("Illegal jump instruction");
    }
    state->setLines(m_value);
}