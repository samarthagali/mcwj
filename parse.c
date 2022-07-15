#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum tok{ ADD,SUB,MUL,DIV,INT }op;

struct tnode{
    int type;
    int val;
    struct tnode*left,*right,*parent;    
};

char stack[20];
int top=-1;
void push(char ele){
        stack[++top]=ele;
}
int m=0;
char pop(){
    // printf(" stack->%c\n",stack[top]);
    return((char)(stack[top--]));
}
void display(){
    int i;
    for(i=0;i<-top;i++){
        printf("%c",stack[i]);
    }
    printf("\n");
}
// enum tok{ plus,minus,mul,divi,expo,intlit }op;
char op1[5]={"+-*/"};
char chcknum[10]={"0123456789"};
int priority(char ele){
    if (ele=='/' || ele=='*'){
        return 3;
    }
    else{
        return 2;
    }
}
int countop=0;
int checkop=0;
char post[20];
char *tokstr[] ={"+","-","*","/"};

void postfix(char infix[]){
    char c;      
    int i =0;
    int j=0;
    while((c=infix[i++])!='\0'){
        if isdigit(c){
            post[j++]=c;
        }
        else if(strchr(op1,c)){
            while(priority(stack[top])>=priority(c)&&top!=-1){
                post[j++]=pop();
            }
            push(c);
            countop++;
        }
        else{
            fprintf(stderr,"UNIDENTIFIED LITERAL %c FOR EXPRESSION",c);
            exit (1);
        }
    }
    m=i-1;
    while(top!=-1){
        post[j++]=pop();
    }
    if(m-countop!=countop+1){
        fprintf(stderr,"invalid expression");
        exit(1);
    }
    else{
        return;
    }
}
struct tnode*root1=NULL;
struct tnode*root2=NULL;
int i =0;
void put(){
    char c;
    // printf("\n%d",i);
    while(isdigit(c=post[i++])){
        push(c);
    }
    int j;
    for (j=0;j<top;j++){
        printf("\n%c",stack[top]);
    }
    struct tnode* n1=(struct tnode*)malloc(sizeof(struct tnode));
    struct tnode* n2=(struct tnode*)malloc(sizeof(struct tnode));
    struct tnode* n3=(struct tnode*)malloc(sizeof(struct tnode));
    char d=post[--i];
    n1->val=-1;
    if(c=='+'){
                n1->type=ADD;
            }
            else if(c=='-'){
                n1->type=SUB;
            }
            else if(c=='*'){
                n1->type=MUL;
            }
            else if(c=='/'){
                n1->type=DIV;
            }

    if (root1==NULL){
       root1=n1;
       n2->val=0+(pop()-'0');
       n3->val=0+(pop()-'0');
       n2->type=n3->type=INT;
       n2->left=n3->left=NULL;
       n3->right=n2->right=NULL;
       n2->parent=n3->parent=n1;
       n1->left=n3;
       n1->right=n2;
    //    printf("%d %d %d",n1->op,n2->op,n3->op);
    
    }
    else{
        if(top==0){
            n1->left=root1;
            n2->type=INT;
            n2->val=0+pop()-'0';
            n1->right=n2;
            n2->left=n3->left=n2->right=n3->right=NULL;
            root1=n1;
        }
        else if(top>=1){
            int j;
           for(j=i;j<=top;j++){
            printf("%c ",post[j]);
           }
           n2->type=INT;
           n3->type=INT;
           n2->val=0+pop()-'0';
           n3->val=0+pop()-'0';
        //    printf("%c",n3->val);
           n1->right=n2;
           n1->left=n3;
           n2->parent=n3->parent=n1;
           n2->left=n3->left=n2->right=n3->right=NULL;
           root2=n1;
        }
        else{
            n1->right=root2;
            n1->left=root1;
            root1=n1;
            root2=NULL;
        }
    }
    i++;
}

void inorder(struct tnode* root){
    if (root==NULL){
        return;
    }
    inorder(root->left);
    if (root->val!=-1){
        printf("%d ",root->val);
    }
    else{
        printf("%s ",tokstr[root->type]);
    }
    inorder(root->right);
}

void main(){
    char infix[20];
    scanf("%s",infix);
    postfix(infix);
    while(checkop!=countop){
        put();
        checkop++;
    }
    printf("len of infix is %d",m);
    // printf("%d",temp->op);
    printf("\n inorder:");
    inorder(root1);
    exit (0);
    // printf("bye");
}


