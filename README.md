# mcwj

My main goal for this was to build a barebones interpreter that can read mathematical expressions, parse them and return the result. It had 3 main parts:
            1)Lexer
            2)Parser
            3)Interpreter
Following this I want to extend this to compile to x86 and then use the compiler to compile a subset of the C language: input, output, variable handling(int,float,char) conditional statements and looping.

1)lexer:A  lexer that  scans and stores each part of the expression
Each part of the expression is stored in a linked list
```
struct token{
int type, intlit;
struct token* next,* prev;
};
```

Each operator is assigned to an integer value(of token type) to make storage of data easier 
The interpreter doesn't store negative values so each operator is assigned a value of -1


2)parser:Generates an abstract syntax tree that classifies the tree and shows the order of execution of given expression
The  parser checks the syntax of the given expression
```
2+3 is a valid expression

2++ is not a valid expression

23+ is a valid expression

+23 is also a valid expression

a+2 is invalid

+,-,*,/,1,2,3,4,5,6,7,8,9 are valid
```
as can be seen, the parser doesn't check if the exp is in infix, prefix, or postfix form

The structure of the tree can be seen below:
```
>struct tnode{
int type, value;
struct tnode*left,*right,*parent;    
};
```
3) Interpreter for the past: This is a non-necessary part of the compiler that I created because I thought it would help me understand exactly how the expressions are to be evaluated and converted to assembly.
Its basic function is to interpret the ast in the correct order

#interpreter for expression tree
interprets the ast we've built in the parser folder

eval function starts from the bottom left of the tree and moves up
```
void eval(struct tnode* root){
if (root->left==NULL||root->right==NULL){
return;}
eval(root->left);
if(root->left->type==INT&&root->right->type==INT&&root->type!=INT){
if(root->type==ADD){
root->val=root->left->val+root->right->val;}
else if(root->type==SUB){
root->val=root->left->val-root->right->val;}
else if(root->type==MUL){
root->val=root->left->val*root->right->val; }
else{
root->val=root->left->val/root->right->val;}
root->type=INT;}
else{
eval(root->right);  }
eval(root->right);}
```
prints the  result of the correctly evaluated expression to stdout
