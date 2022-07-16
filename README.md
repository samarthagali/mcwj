# mcwj
##my first ever compiler so pls be nice

My main goal for this was to build a barebones compiler that can compile mathematical expressions into x86 assembly.The compiler had 3 main parts:
            1)Lexer
            2)Parser
            3)Code generator
1)lexer:A barebones lexer that does nothing but scanning and storing each part of the expression
Each part of the expression is stored in a linked list
>struct token{

>   int type, intlit;

>   struct token* next,* prev;

>};


Each operator is assigned to an integer value(of token type) to make storage of data easier 
The compiler doesn't store negative values so each operator is assigned a value of -1


2)parser:Generates an abstract syntax tree that classifies the tree and shows the order of execution of given expression
