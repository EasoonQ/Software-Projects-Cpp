# HW2

This program can interpret a self-defined language, which has the following valid statements:

LET *var* *int*  | Change the value of variable *var* to the integer *int*

PRINT *var*      | Print the value of variable *var* to output

PRINTALL         | Prints the value of all used variables to output, one per line.

ADD *var* *p*    | Adds *p* to the value of the variable *var*, where *p* is an int or variable.

SUB *var* *p*    | Subtracts *p* from  the value of the variable *var*, where *p* is an int or variable.

MULT *var* *p*   | Multiplies the value of the variable *var* by the integer or variable *p*

DIV *var* *p*    | Divides the value of the variable *var* by the integer or variable *p*

GOTO *linenum*   | Jumps execution of the program to the line numbered *linenum*

IF *var* *op*    | Compares the value of the variable *var* to the integer *int*
*int* THEN       | via the operator *op* (<, <=, >, >=, =, <>), and jumps
*linenum*        | execution of the program to line *linenum* if true.

GOSUB *linenum*  | Temporarily jumps to line *linenum*, and jumps back after a RETURN

RETURN           | Jumps execution of the program back to the most recently executed GOSUB.

END              | Immediately terminates the program.

.                | Placed at the end of the program, and behaves like an END statement.

A sample valid program could be:

1 LET KYLO 1
2 GOSUB 7
3 PRINT KYLO
4 END
5 LET KYLO 3
6 RETURN
7 PRINT KYLO
8 LET KYLO 2
9 GOSUB 5
10 PRINT KYLO
11 RETURN
12 .

To compile the code, use "make all", and an executable named "interpreter" will be created.
Use ./interpreter to start the program, then it will lead to you enter the input file name.

A test.txt is provided in the folder, you may make changes to it and use it as the input file.
