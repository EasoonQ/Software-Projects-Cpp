// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <map>
#include <stack>
#include <string>

class ProgramState {
public:
    ProgramState(int numLines);
    ~ProgramState();
    // You'll need to add a variety of methods here.  Rather than trying to
    // think of what you'll need to add ahead of time, add them as you find
    // that you need them.
    int getLines();
    void setLines(int lines);
    int getVariables(std::string name);            // get the variable given the name
    std::map<std::string, int> getAllVariables();  // get the map of all variables
    void setVariables(std::string name, int val);
    int getRe();
    void setRe(int val);
    bool emptyRe();  // check if the stack is empty
    void addline();
    int getMaxNumLine();
    void setMaxNumLine(int val);
    bool varExist(std::string var);  // given a variable name, check if it has been declared
private:
    int m_numLines;                        // indicate which line the program is now running
    std::map<std::string, int> variables;  // store variables and their values
    std::stack<int> re;                    // stack used for RETURN
    int maxNumLine;                        // the total num of line of the program
};

#endif
