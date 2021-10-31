#include "PrintallStatement.h"

PrintallStatement::PrintallStatement() {}
PrintallStatement::~PrintallStatement() {}

void PrintallStatement::execute(ProgramState* state, std::ostream& outf) {
    std::map<std::string, int> a = state->getAllVariables();
    // iterator to print out all the variables and their values
    for (std::map<std::string, int>::iterator it = a.begin(); it != a.end(); ++it) {
        outf << it->first << " " << it->second << std::endl;
    }
    state->addline();
}
