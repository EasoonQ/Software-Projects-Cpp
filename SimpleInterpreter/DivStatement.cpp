#include "DivStatement.h"

#include "math.h"
#include <stdexcept>

DivStatement::DivStatement(std::string name, std::string div) : m_name(name), m_div(div) {}
DivStatement::~DivStatement() {}

void DivStatement::execute(ProgramState* state, std::ostream& outf) {
    if (!state->varExist(m_name)) {
        state->setVariables(m_name, 0);  // if use undeclared variable, set its value to 0
    }
    if (isdigit(m_div[0]) || (m_div[0] == '-')) {  // check if first digit is number or negative sign
        if (stoi(m_div) == 0) {                    // check if divide by 0
            throw std::invalid_argument("Divide by zero exception");
        } else {
            state->setVariables(m_name, floor((double)state->getVariables(m_name) / (double)stoi(m_div)));
        }
    } else {  // otherwise this would be another variable name
        if (!state->varExist(m_div)) {
            state->setVariables(m_div, 0);  // if use undeclared variable, set its value to 0
        }
        if (state->getVariables(m_div) == 0) {  // check if divide by 0
            throw std::invalid_argument("Divide by zero exception");
        } else {  // operate division with round-down
            state->setVariables(
                    m_name, floor((double)state->getVariables(m_name) / (double)state->getVariables(m_div)));
        }
    }
    state->addline();
}
