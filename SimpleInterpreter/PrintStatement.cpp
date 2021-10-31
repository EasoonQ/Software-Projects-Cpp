#include "PrintStatement.h"

PrintStatement::PrintStatement(std::string variableName) : m_variableName(variableName) {}
PrintStatement::~PrintStatement() {}

void PrintStatement::execute(ProgramState* state, std::ostream& outf) {
    int val = 0;
    if (state->varExist(m_variableName)) {
        val = state->getVariables(m_variableName);
    } else {
        state->setVariables(m_variableName, 0);  // if use undeclared variable, set its value to 0
    }
    outf << val << std::endl;
    state->addline();
}
