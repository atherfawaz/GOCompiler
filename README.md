# GO--Compiler

A tiny compiler for Go-- language written in C++20 for our course on Compiler Construction.

## Setup

We used the compiler [mingw](https://nav.dl.sourceforge.net/project/mingw-w64/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe) to run our code in [Clion 2021](https://www.jetbrains.com/clion/).

```bash
git clone https://github.com/atherfawaz/GOCompiler.git
```

## Running the program

```bash
Open folder in Clion
Ensure that the right compiler is selected
Run the program

```
Our lexer will be accepting any input file containing GO-- source code.

## Expected Input

The compiler takes a .go file. An example could be the following source code.

```go
func integer: numPrint (integer: num, integer: length) {
	integer: i, j, z, sqr;
	i := 2;
	in >> j;
	if j > 3 : {
    z := 3 * i + j;
	}
	else {
    z := 42;
	}
	print(z);
	while i < 10: {
    sqr := i * i;
    print(sqr);
    i := i + 1;
	 }
}
```
## Generated Tokens

```
KEYWORD func row 0 col 3
KEYWORD integer row 0 col 11
VAR_DEC : row 0 col 12
IDENTIFIER numPrint row 0 col 21
PRNT ( row 0 col 23
KEYWORD integer row 0 col 30
VAR_DEC : row 0 col 31
IDENTIFIER num row 0 col 35
COMMA , row 0 col 36
KEYWORD integer row 0 col 44
VAR_DEC : row 0 col 45
IDENTIFIER length row 0 col 52
PRNT ) row 0 col 53
BRACES { row 0 col 55
KEYWORD integer row 1 col 12
VAR_DEC : row 1 col 13
IDENTIFIER i row 1 col 15
COMMA , row 1 col 16
IDENTIFIER j row 1 col 18
COMMA , row 1 col 19
IDENTIFIER z row 1 col 21
COMMA , row 1 col 22
IDENTIFIER sqr row 1 col 26
SEMICOLON ; row 1 col 27
IDENTIFIER i row 2 col 6
ASS_OP := row 2 col 9
NUMBER 2 row 2 col 11
SEMICOLON ; row 2 col 12
KEYWORD in row 3 col 7
INPUT_OP >> row 3 col 10
IDENTIFIER j row 3 col 12
SEMICOLON ; row 3 col 13
KEYWORD if row 4 col 7
IDENTIFIER j row 4 col 9
RO_OP > row 4 col 11
NUMBER 3 row 4 col 13
VAR_DEC : row 4 col 15
BRACES { row 4 col 17
IDENTIFIER z row 5 col 10
ASS_OP := row 5 col 13
NUMBER 3 row 5 col 15
AR_OP * row 5 col 17
IDENTIFIER i row 5 col 19
AR_OP + row 5 col 21
IDENTIFIER j row 5 col 23
SEMICOLON ; row 5 col 24
BRACES } row 6 col 7
KEYWORD else row 7 col 10
BRACES { row 7 col 12
IDENTIFIER z row 8 col 10
ASS_OP := row 8 col 13
NUMBER 42 row 8 col 16
SEMICOLON ; row 8 col 17
BRACES } row 10 col 7
KEYWORD print row 11 col 11
PRNT ( row 11 col 12
IDENTIFIER z row 11 col 13
PRNT ) row 11 col 14
SEMICOLON ; row 11 col 15
KEYWORD while row 12 col 11
IDENTIFIER i row 12 col 13
RO_OP < row 12 col 15
NUMBER 10 row 12 col 18
VAR_DEC : row 12 col 19
BRACES { row 12 col 21
IDENTIFIER sqr row 13 col 11
ASS_OP := row 13 col 14
IDENTIFIER i row 13 col 16
AR_OP * row 13 col 18
IDENTIFIER i row 13 col 20
SEMICOLON ; row 13 col 21
KEYWORD print row 14 col 13
PRNT ( row 14 col 14
IDENTIFIER sqr row 14 col 17
PRNT ) row 14 col 18
SEMICOLON ; row 14 col 19
IDENTIFIER i row 15 col 9
ASS_OP := row 15 col 12
IDENTIFIER i row 15 col 14
AR_OP + row 15 col 16
NUMBER 1 row 15 col 18
SEMICOLON ; row 15 col 19
BRACES } row 18 col 7
BRACES } row 21 col 1
```
## Generated Symbol Table

```
integer:i:0
integer:j:4
integer:sqr:8
integer:z:12
```

## Generated Parse Tree

```
START_PARSE     
PROGRAM_START     
PROGRAM_START     func
|---FUNC_HEADER     func
|   |---FUNC_HEADER     func
|   |---RETURN_TYPE     integer
|   |---FUNC_HEADER     :
|   |---IDENTIFIER     numPrint
|   |   |---ALPHABET     
|   |   |---ALPHANUMERIC     
|   |---FUNC_HEADER     (
|   |---PARAMETERS     
|   |   |---DATATYPE     integer
|   |   |---DATATYPE     integer
|   |   |---PARAMETERS     :
|   |   |---IDENTIFIER     num
|   |   |   |---ALPHABET     
|   |   |   |---ALPHANUMERIC     
|   |---ADDITIONAL_PARAMETERS     ,
|   |---ADDITIONAL_PARAMETERS     ,
|   |---PARAMETERS     
|   |   |---DATATYPE     integer
|   |   |---DATATYPE     integer
|   |   |---PARAMETERS     :
|   |   |---IDENTIFIER     length
|   |   |   |---ALPHABET     
|   |   |   |---ALPHANUMERIC     
|   |---ADDITIONAL_PARAMETERS     )
|   |---FUNC_HEADER     )
|   |---FUNC_HEADER     {
|   |---STATEMENT     
|   |   |---INT_DECLARATION     integer
|   |   |   |---INT_DECLARATION     integer
|   |   |   |---INT_DECLARATION     :
|   |   |   |---IDENTIFIER     i
|   |   |   |   |---ALPHABET     
|   |   |   |   |---ALPHANUMERIC     
|   |   |---ADD_INT_DEC     ,
|   |   |   |---ADD_INT_DEC     ,
|   |   |   |---IDENTIFIER     j
|   |   |   |   |---ALPHABET     
|   |   |   |   |---ALPHANUMERIC     
|   |   |---ADD_INT_DEC     ,
|   |   |   |---ADD_INT_DEC     ,
|   |   |   |---IDENTIFIER     z
|   |   |   |   |---ALPHABET     
|   |   |   |   |---ALPHANUMERIC     
|   |   |---ADD_INT_DEC     ,
|   |   |   |---ADD_INT_DEC     ,
|   |   |   |---IDENTIFIER     sqr
|   |   |   |   |---ALPHABET     
|   |   |   |   |---ALPHANUMERIC     
|   |   |---ADD_INT_DEC     ;
|   |   |   |---INT_DECLARATION     ;
|   |---STATEMENT     
|   |   |---IDENTIFIER     i
|   |   |   |---ALPHABET     
|   |   |   |---ALPHANUMERIC     
|   |   |---NUMBER     2
|   |   |---ASSIGNMENT     :=
|   |   |   |---ASSIGNMENT     :=
|   |   |   |---TO_ASSIGN     
|   |   |   |---NUMBER     2
|   |   |   |---ASSIGNMENT     ;
|   |---STATEMENT     
|   |   |---INPUT     in
|   |   |   |---INPUT     in
|   |   |   |---INPUT     >>
|   |   |   |---IDENTIFIER     j
|   |   |   |   |---ALPHABET     
|   |   |   |   |---ALPHANUMERIC     
|   |   |---INPUT     ;
|   |---STATEMENT     
|   |   |---IF     if
|   |   |   |---IF     if
|   |   |   |---COMPARISON     
|   |   |   |   |---CONDITIONAL     
|   |   |   |   |   |---IDENTIFIER     j
|   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---RELATIONAL_OP     >
|   |   |   |   |---CONDITIONAL     
|   |   |   |   |   |---NUMBER     3
|   |   |   |   |---ADDITIONAL_COMP     :
|   |   |   |---IF     :
|   |   |   |---IF     {
|   |   |   |---STATEMENT     
|   |   |   |   |---IDENTIFIER     z
|   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---NUMBER     3
|   |   |   |   |---EXPRESSION     3
|   |   |   |   |   |---MUL_DIV     
|   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |---NUMBER     3
|   |   |   |   |   |   |---MUL_DIV_     *
|   |   |   |   |   |   |   |---MUL_DIV_     *
|   |   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |   |   |---MUL_DIV_     +
|   |   |   |   |   |---ADD_SUB     +
|   |   |   |   |   |   |---ADD_SUB     +
|   |   |   |   |   |   |---MUL_DIV     
|   |   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |   |---IDENTIFIER     j
|   |   |   |   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |   |   |---MUL_DIV_     ;
|   |   |   |   |   |   |---ADD_SUB     ;
|   |   |   |---STATEMENT     
|   |   |   |---IF     }
|   |   |   |---IF     else
|   |   |   |---ELSE     else
|   |   |   |   |---ELSE     else
|   |   |   |   |---ELSE     {
|   |   |   |   |---STATEMENT     
|   |   |   |   |   |---IDENTIFIER     z
|   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |---NUMBER     42
|   |   |   |   |   |---ASSIGNMENT     :=
|   |   |   |   |   |   |---ASSIGNMENT     :=
|   |   |   |   |   |   |---TO_ASSIGN     
|   |   |   |   |   |   |---NUMBER     42
|   |   |   |   |   |   |---ASSIGNMENT     ;
|   |   |   |   |---STATEMENT     
|   |   |   |   |---ELSE     }
|   |---STATEMENT     
|   |   |---PRINTS     print
|   |   |   |---PRINTS     print
|   |   |   |---PRINTS     (
|   |   |   |---TO_PRINT     
|   |   |   |   |---IDENTIFIER     z
|   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |---PRINTS     )
|   |   |   |---PRINTS     ;
|   |---STATEMENT     
|   |   |---LOOP     while
|   |   |   |---LOOP     while
|   |   |   |---COMPARISON     
|   |   |   |   |---CONDITIONAL     
|   |   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---RELATIONAL_OP     <
|   |   |   |   |---CONDITIONAL     
|   |   |   |   |   |---NUMBER     10
|   |   |   |   |---ADDITIONAL_COMP     :
|   |   |   |---LOOP     :
|   |   |   |---LOOP     {
|   |   |   |---STATEMENT     
|   |   |   |   |---IDENTIFIER     sqr
|   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---EXPRESSION     i
|   |   |   |   |   |---MUL_DIV     
|   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |   |---MUL_DIV_     *
|   |   |   |   |   |   |   |---MUL_DIV_     *
|   |   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |   |   |---MUL_DIV_     ;
|   |   |   |   |   |---ADD_SUB     ;
|   |   |   |---STATEMENT     
|   |   |   |   |---PRINTS     print
|   |   |   |   |   |---PRINTS     print
|   |   |   |   |   |---PRINTS     (
|   |   |   |   |   |---TO_PRINT     
|   |   |   |   |   |   |---IDENTIFIER     sqr
|   |   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |---PRINTS     )
|   |   |   |   |   |---PRINTS     ;
|   |   |   |---STATEMENT     
|   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |---EXPRESSION     i
|   |   |   |   |   |---MUL_DIV     
|   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |---IDENTIFIER     i
|   |   |   |   |   |   |   |   |---ALPHABET     
|   |   |   |   |   |   |   |   |---ALPHANUMERIC     
|   |   |   |   |   |   |---MUL_DIV_     +
|   |   |   |   |   |---ADD_SUB     +
|   |   |   |   |   |   |---ADD_SUB     +
|   |   |   |   |   |   |---MUL_DIV     
|   |   |   |   |   |   |   |---FINAL     
|   |   |   |   |   |   |   |   |---NUMBER     1
|   |   |   |   |   |   |   |---MUL_DIV_     ;
|   |   |   |   |   |   |---ADD_SUB     ;
|   |   |   |---STATEMENT     
|   |---LOOP     }
|   |---STATEMENT     
FUNC_HEADER     }
```

## Generated Three-Address-Code
The compiler then converts the input file into a traditional three-address-code. The provided interpreter can run this three-address-code directly. 

```
i = 2
in j
if j > 3 goto 5 
goto 9 
temp0 = 3 * i
temp1 = temp0 + j
z = temp1
goto 10 
z = 42
out z
Wif i < 10 goto 13 
goto 19 
temp0 = i * i
sqr = temp0
out sqr
temp0 = i + 1
i = temp0
goto 11
```

## Generated Machine Code
The compiler can also convert it directly in machine code. This can be run as well, producing the same output as the interpreted code.

```
1 1 2 
11 3 
7 3 4 5 
13 9 
4 6 2 5 
2 5 3 7 
1 7 8 
13 10 
1 9 8 
12 8 
6 2 10 13 
13 19 
4 2 2 5 
1 5 11 
12 11 
2 2 12 5 
1 5 2 
13 11 
```
