// / C program for expression tree implementation  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <ctype.h>  
/* The below structure node is defined as a node of a binary tree consists  
of left child and the right child, along with the pointer next which points to the next node */  
char stack[20];
int top=-1;
void push(char ele){
    stack[++top]=ele;
}
enum tok{ADD,SUB,MUL,DIV,INT}op;
char pop(){
    return(stack[top--]);   
}
struct node   
{  
    int type,val ;  
    struct node* left ;  
    struct node* right ;  
    struct node* nxt ;  
};
char post[20];
int priority(char ele){
    if(ele=='/'){
        return 4;
    }
    else if ( ele=='*'){
        return 3;
    }
    else if(ele=='+'){
        return 2;
    }
    else{
        return 1;
    }
}
int m=0;
int countop=0;
char op1[5]={"+-*/"};
void postfix(char infix[]){
    char c;      
    int i =0;
    int j=0;
    while((c=infix[i++])!='\0'){
        if (isdigit(c)){
            post[j++]=c;
            m++;
        }
        else if(strchr(op1,c)){
            while(priority(stack[top])>=priority(c)&&top!=-1){
                post[j++]=pop();
            }
            push(c);
        }
        else if(c==' '||c=='\n'||c==EOF){
            continue;
        }
        else{
            fprintf(stderr,"UNIDENTIFIED LITERAL %c FOR EXPRESSION",c);
            exit (1);
        }
    }
    while(top!=-1){
        post[j++]=pop();
    }
    return;
}
struct node *head=NULL;  
/* Helper function that allocates a new node with the 
given data and NULL left and right pointers. */  
struct node* newnode(int type,int val)  
{  
    struct node* node = (struct node*) malloc ( sizeof ( struct node ) ) ;  
    node->type = type ;
    node->val=val;  
    node->left = NULL ;  
    node->right = NULL ;  
    node->nxt = NULL ;  
    return ( node ) ;  
}  
void Inorder(struct node* root)  
{  
    if (root->left==NULL||root->right==NULL){
        return;
    }
    Inorder(root->left);
    if(root->left->type==INT&&root->right->type==INT&&root->type!=INT){
        if(root->type==ADD){
            root->val=root->left->val+root->right->val;
        }
        else if(root->type==SUB){
            root->val=root->left->val-root->right->val;
        }
        else if(root->type==MUL){
            root->val=root->left->val*root->right->val;
        }
        else{
            root->val=root->left->val/root->right->val;
        }
        root->type=INT;
    }
    else{
        Inorder(root->left);
    }
    // printf("%d %d  ",root->type,root->val);

    Inorder(root->right);
}  
void inorder(struct node*root) {
    if(root==NULL){
        return;
    }
    inorder(root->left);
    printf("%d ",root->val);
    inorder(root->right);
} 
void pushnode ( struct node* x )  
{  
    if ( head == NULL )  
    head = x ;  
    else  
    {  
        ( x )->nxt = head ;  
        head = x ;  
    }  
    // struct node* temp ;  
    // while ( temp != NULL )  
    // {  
    //   printf ( " %c " , temp->info ) ;  
    //   temp = temp->nxt ;  
    // }  
}  
struct node* popnode()  
{  
    // Poping out the top most [pointed with head] element  
    struct node* n = head ;  
    head = head->nxt ;  
    return n ;  
}
int main(int argc,char**argv)  
{  
    if(argc!=2){
        printf("Incorrectly passed arugments to interpreter\n");
        fprintf(stderr,"exited with status 1\n");
        exit(1);
    }
    FILE *ptr;
    ptr=fopen(argv[1],"r");
    if(ptr==NULL){
        printf("error cannot find file %s]n",argv[1]);
    }
    char infix[20];  
    int i=0;
    while (!feof(ptr)) {
        infix[i] = fgetc(ptr);
        if(strchr(op1,infix[i])){
            m++;
            countop++;
        }
        else if isdigit(infix[i]){
            m++;
        }
        else{
            continue;
        }
        i++;
    }
   if(m-countop!=countop+1){
        fprintf(stderr,"invalid expression");
        exit(1);
    }
    fclose(ptr);
    i=0;
    postfix(infix);
    // printf("%s\n",post);
    struct node*p,*q,*s;
    int type;
    while ( post[i]!='\0' )   
    {  
        // if read character is operator then popping two  
        // other elements from stack and making a binary  
        // tree  
        if (strchr(op1,post[i]) )  
        {  
            if(post[i]=='+'){
                type=ADD;
            }
            else if(post[i]=='-'){
                type=SUB;
            }
            else if(post[i]=='*'){
                type=MUL;
            }
             else{
                type=DIV;
            }
            s = newnode (type,-1) ;  
            p = popnode() ;  
            q = popnode() ;  
            s->left = q ;  
            s->right = p;  
            pushnode(s);  
        }  
        else {  
            s = newnode ( INT,post [ i ]-'0' ) ;   
            pushnode ( s ) ;  
        }
        i++;  
    }  
    printf ( " Evaluated expression tree is:" ) ;  
    struct node*temp=s;
    while(temp->type!=INT){
        Inorder(s);
    }
    printf("%d\n",temp->val);  
    exit(0) ;  
}  
