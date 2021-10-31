#include "EndStatement.h"
EndStatement::EndStatement() {}
EndStatement::~EndStatement() {}

void EndStatement::execute(ProgramState* state, std::ostream& outf) {
    exit(0);  // successful exit
}
