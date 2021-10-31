all: Interpret

Interpret: Interpreter.cpp ProgramState.o LetStatement.o PrintStatement.o PrintallStatement.o AddStatement.o SubStatement.o MultStatement.o DivStatement.o GotoStatement.o IfStatement.o GosubStatement.o ReturnStatement.o EndStatement.o DotStatement.o
	g++ -g -Wall $^ -o interpreter

ProgramState.o: ProgramState.h ProgramState.cpp Statement.h
	g++ -g -Wall -c ProgramState.cpp -o ProgramState.o

LetStatement.o: LetStatement.h LetStatement.cpp Statement.h
	g++ -g -Wall -c LetStatement.cpp -o LetStatement.o

PrintStatement.o: PrintStatement.h PrintStatement.cpp Statement.h
	g++ -g -Wall -c PrintStatement.cpp -o PrintStatement.o

PrintallStatement.o: PrintallStatement.h PrintallStatement.cpp Statement.h
	g++ -g -Wall -c PrintallStatement.cpp -o PrintallStatement.o

AddStatement.o: AddStatement.h AddStatement.cpp Statement.h
	g++ -g -Wall -c AddStatement.cpp -o AddStatement.o

SubStatement.o: SubStatement.h SubStatement.cpp Statement.h
	g++ -g -Wall -c SubStatement.cpp -o SubStatement.o

MultStatement.o: MultStatement.h MultStatement.cpp Statement.h
	g++ -g -Wall -c MultStatement.cpp -o MultStatement.o

DivStatement.o: DivStatement.h DivStatement.cpp Statement.h
	g++ -g -Wall -c DivStatement.cpp -o DivStatement.o

GotoStatement.o: GotoStatement.h GotoStatement.cpp Statement.h
	g++ -g -Wall -c GotoStatement.cpp -o GotoStatement.o

IfStatement.o: IfStatement.h IfStatement.cpp Statement.h
	g++ -g -Wall -c IfStatement.cpp -o IfStatement.o

GosubStatement.o: GosubStatement.h GosubStatement.cpp Statement.h
	g++ -g -Wall -c GosubStatement.cpp -o GosubStatement.o

ReturnStatement.o: ReturnStatement.h ReturnStatement.cpp Statement.h
	g++ -g -Wall -c ReturnStatement.cpp -o ReturnStatement.o

EndStatement.o: EndStatement.h EndStatement.cpp Statement.h
	g++ -g -Wall -c EndStatement.cpp -o EndStatement.o

DotStatement.o: DotStatement.h DotStatement.cpp Statement.h
	g++ -g -Wall -c DotStatement.cpp -o DotStatement.o


