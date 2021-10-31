#include "IfStatement.h"

#include <stdexcept>

IfStatement::IfStatement(std::string variable, std::string operation, int val, int linenum) {
    m_variable = variable;
    m_operation = operation;
    m_val = val;
    m_linenum = linenum;
}
IfStatement::~IfStatement() {}

void IfStatement::execute(ProgramState* state, std::ostream& outf) {
    // check if the target line is out of range
    if ((m_linenum < 1) || (m_linenum > state->getMaxNumLine())) {
        throw std::invalid_argument("Illegal jump instruction");
    } else {
        if (!state->varExist(m_variable)) {
            state->setVariables(m_variable, 0);  // if use undeclared variable, set its value to 0
        }
        // do operations based on operation sign
        if (m_operation == ">") {
            if (state->getVariables(m_variable) > m_val) {
                state->setLines(m_linenum);
            }
        }
        if (m_operation == ">=") {
            if ((state->getVariables(m_variable) > m_val) || state->getVariables(m_variable) == m_val) {
                state->setLines(m_linenum);
            }
        }
        if (m_operation == "<") {
            if (state->getVariables(m_variable) < m_val) {
                state->setLines(m_linenum);
            }
        }
        if (m_operation == "<=") {
            if ((state->getVariables(m_variable) < m_val) || (state->getVariables(m_variable) == m_val)) {
                state->setLines(m_linenum);
            }
        }
        if (m_operation == "=") {
            if (state->getVariables(m_variable) == m_val) {
                state->setLines(m_linenum);
            }
        }
        if (m_operation == "<>") {
            if (state->getVariables(m_variable) != m_val) {
                state->setLines(m_linenum);
            }
        }
    }
}
