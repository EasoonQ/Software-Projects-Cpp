#include "ProgramState.h"

ProgramState::ProgramState(int numLines) : m_numLines(numLines) {}

ProgramState::~ProgramState() {}

int ProgramState::getLines() { return m_numLines; }

void ProgramState::setLines(int lines) { m_numLines = lines; }

// get the variable given the name
int ProgramState::getVariables(std::string name) { return variables[name]; }

// get the map of all variables
std::map<std::string, int> ProgramState::getAllVariables() { return variables; }

void ProgramState::setVariables(std::string name, int val) { variables[name] = val; }

int ProgramState::getRe() {
    int a = re.top();
    re.pop();
    return a;
}

void ProgramState::setRe(int val) { re.push(val); }

// check if the stack is empty
bool ProgramState::emptyRe() { return (re.empty()); }

void ProgramState::addline() { ++m_numLines; }

int ProgramState::getMaxNumLine() { return maxNumLine; }

void ProgramState::setMaxNumLine(int val) { maxNumLine = val; }

// given a variable name, check if it has been declared
bool ProgramState::varExist(std::string var) {
    for (std::map<std::string, int>::iterator it = variables.begin(); it != variables.end(); ++it) {
        if (it->first == var) {
            return true;
        }
    }
    return false;
}
