#include "MultStatement.h"

MultStatement::MultStatement(std::string name, std::string mult) : m_name(name), m_mult(mult) {}
MultStatement::~MultStatement() {}

void MultStatement::execute(ProgramState* state, std::ostream& outf) {
    if (!state->varExist(m_name)) {
        state->setVariables(m_name, 0);  // if use undeclared variable, set its value to 0
    }
    if (isdigit(m_mult[0]) || (m_mult[0] == '-')) {  // check if first digit is number or negative sign
        state->setVariables(m_name, state->getVariables(m_name) * stoi(m_mult));
    } else {  // otherwise this would be another variable name
        if (!state->varExist(m_mult)) {
            state->setVariables(m_mult, 0);  // if use undeclared variable, set its value to 0
        }
        state->setVariables(m_name, state->getVariables(m_name) * state->getVariables(m_mult));
    }
    state->addline();
}
