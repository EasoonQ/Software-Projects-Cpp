#include "AddStatement.h"

AddStatement::AddStatement(std::string name, std::string add) : m_name(name), m_add(add) {}
AddStatement::~AddStatement() {}

void AddStatement::execute(ProgramState* state, std::ostream& outf) {
    if (!state->varExist(m_name)) {
        state->setVariables(m_name, 0);  // if use undeclared variable, set its value to 0
    }
    if (isdigit(m_add[0]) || (m_add[0] == '-')) {  // check if first digit is number or negative sign
        state->setVariables(m_name, state->getVariables(m_name) + stoi(m_add));
    } else {  // otherwise this would be another variable name
        if (!state->varExist(m_add)) {
            state->setVariables(m_add, 0);  // if use undeclared variable, set its value to 0
        }
        state->setVariables(m_name, state->getVariables(m_name) + state->getVariables(m_add));
    }
    state->addline();
}
