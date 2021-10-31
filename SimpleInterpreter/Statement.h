#ifndef STATEMENT_INCLUDED
#define STATEMENT_INCLUDED

#include "ProgramState.h"
#include <fstream>

class Statement {
    // execute() takes a ProgramState and executes this statement, by making
    // any necessary changes to the ProgramState (e.g. a new value for the
    // program counter, changing the value of some variable, pushing or
    // popping from the line number stack).
    // execute() also takes an ostream parameter;  if any output is to be
    // written, write it to the given ostream.

    //
    // In the event that the execution of the statement causes a fatal error
    // that should terminate the BASIC program, such as division by zero or
    // a RETURN statement without a corresponding GOSUB, the program may exit
    // instead of returning from execute().
public:
    virtual void execute(ProgramState* state, std::ostream& outf) = 0;
    virtual ~Statement(){};
};

#endif
