#include "DotStatement.h"
DotStatement::DotStatement() {}
DotStatement::~DotStatement() {}

void DotStatement::execute(ProgramState* state, std::ostream& outf) {
    exit(0);  // successful exit
}
