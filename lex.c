#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum tok{ plus,minus,mul,divi,expo,intlit }op;
struct token{
    int type;
    int intlit;
    struct token* next;
    struct token* prev;
};
struct token*root=NULL;

char nos[10]={"0123456789"};

// int chrpos(char c){
//     int i=0;
//     printf("%c",c);
//     // while(nos[i]!=c){
//     //     i++;
//     // }
//     return i;
// }

// int val(char c,int i,char exp[]){
//     int val=0,pos;
//     while((pos=chrpos(c))>=0){
//         c=exp[i];
//         val=(val*10)+pos;
//         i++;
//     }
//     printf("hiii");
//     return val;
// }
char *tokstr[] ={"+","-","*","/","^","INTLIT"};
// void disp(){
//    printf("bye");
// }

void insertfront(int typ,int no){
    struct token * n1;
    n1=(struct token *)malloc(sizeof(struct token));
    n1->type=typ;
    n1->intlit=no;
    n1->next=NULL;
    n1->prev=NULL;
    if (root==NULL){
        root=n1;
        return;
    }
    n1->next=root;
    n1->next->prev=n1;
    root=n1;        
}

void classify(char exp[1000]){
    char c;
    int i=0;
    struct token*temp;
    while((c=exp[i++])!='\0'){
        if (strchr(nos,c)){
            int k;
            while (strchr(nos,c=exp[i++])){
                k =k+c-'0';
                c=exp[i++]  ;
                }
             insertfront(intlit,k);       
        }
        else{
            if(c=='+'){
                insertfront(plus,-1);
            }
            else if(c=='-'){
                insertfront(minus,-1);
            }
            else if(c=='*'){
                insertfront(mul,-1);
            }
            else if(c=='/'){
                insertfront(divi,-1);
            }
            else if(c=='^'){
                insertfront(expo,-1);
             }
            else{
                printf("not valid");
                return;
            }
            }
        temp=root;
        if (root==NULL){
        printf("root is empty");
        return;
    }}
    i=0;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    while(temp!=NULL    ){
        printf(" token :%s",tokstr[temp->type]);
        if (temp->intlit!=-1){
            printf(" value :%d",temp->intlit);
        }
        printf("\n");
        temp=temp->prev;
    }       
    
}       
void main(){
    char exp[1000];
    scanf("%s",exp);
    classify(exp);
     
 }


// /home/samarth/Documents/compile/lex.c