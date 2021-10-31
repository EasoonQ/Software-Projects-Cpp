#include "AddStatement.h"
#include "DivStatement.h"
#include "DotStatement.h"
#include "EndStatement.h"
#include "GosubStatement.h"
#include "GotoStatement.h"
#include "IfStatement.h"
#include "LetStatement.h"
#include "MultStatement.h"
#include "PrintStatement.h"
#include "PrintallStatement.h"
#include "ReturnStatement.h"
#include "Statement.h"
#include "SubStatement.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement*>& program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement* parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main() {
    cout << "Enter BASIC program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    interpretProgram(infile, cout);
}

void parseProgram(istream& inf, vector<Statement*>& program) {
    program.push_back(NULL);

    string line;
    while (!inf.eof()) {
        getline(inf, line);
        program.push_back(parseLine(line));
    }
}

Statement* parseLine(string line) {
    Statement* statement;
    stringstream ss;
    int num;  // hold the line number for each line
    string type;
    string var;
    string var2;
    int val;
    int val2;
    string op;     // hold operation sign in IfStatement
    string trash;  // hold "then" in IfStatement

    ss << line;
    ss >> num;
    ss >> type;

    if (type == "LET") {
        ss >> var;
        ss >> val;
        // Note:  Because the project spec states that we can assume the file
        //	  contains a syntactically legal program, we know that
        //	  any line that begins with "LET" will be followed by a space
        //	  and then a variable and then an integer value.
        statement = new LetStatement(var, val);
    }

    if (type == "PRINT") {
        ss >> var;
        statement = new PrintStatement(var);
    }

    if (type == "PRINTALL") {
        statement = new PrintallStatement();
    }

    if (type == "ADD") {
        ss >> var >> var2;
        statement = new AddStatement(var, var2);
    }

    if (type == "SUB") {
        ss >> var >> var2;
        statement = new SubStatement(var, var2);
    }

    if (type == "MULT") {
        ss >> var >> var2;
        statement = new MultStatement(var, var2);
    }

    if (type == "DIV") {
        ss >> var >> var2;
        statement = new DivStatement(var, var2);
    }

    if (type == "GOTO") {
        ss >> val;
        statement = new GotoStatement(val);
    }

    if (type == "IF") {
        ss >> var >> op >> val >> trash >> val2;
        statement = new IfStatement(var, op, val, val2);
    }

    if (type == "GOSUB") {
        ss >> val;
        statement = new GosubStatement(val);
    }

    if (type == "RETURN") {
        ss >> val;
        statement = new ReturnStatement(val);
    }

    if (type == "END") {
        statement = new EndStatement();
    }

    if (type == ".") {
        statement = new DotStatement();
    }

    return statement;
}

void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement*> program;
    parseProgram(inf, program);
    ProgramState* a = new ProgramState(1);
    a->setMaxNumLine(program.size() - 1);
    while (!program.empty()) {
        try {  // handle the exception
            program[a->getLines()]->execute(a, outf);
        } catch (const std::invalid_argument& e) {
            outf << e.what() << std::endl;
            exit(-1);
        }
    }
    // clear the memory
    for (int i = 0; i < (int)program.size(); ++i) {
        delete program[i];
    }
    delete a;
}
