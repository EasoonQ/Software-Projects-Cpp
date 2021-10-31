#include "SubStatement.h"

SubStatement::SubStatement(std::string name, std::string sub) : m_name(name), m_sub(sub) {}
SubStatement::~SubStatement() {}

void SubStatement::execute(ProgramState* state, std::ostream& outf) {
    if (!state->varExist(m_name)) {
        state->setVariables(m_name, 0);  // if use undeclared variable, set its value to 0
    }
    if (isdigit(m_sub[0]) || (m_sub[0] == '-')) {  // check if first digit is number or negative sign
        state->setVariables(m_name, state->getVariables(m_name) - stoi(m_sub));
    } else {  // otherwise this would be another variable name
        if (!state->varExist(m_sub)) {
            state->setVariables(m_sub, 0);  // if use undeclared variable, set its value to 0
        }
        state->setVariables(m_name, state->getVariables(m_name) - state->getVariables(m_sub));
    }
    state->addline();
}