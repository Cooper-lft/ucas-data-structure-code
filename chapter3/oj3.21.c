/*
逆波兰式
描述：
假设表达式由单字母变量和双目四则运算符构成.
试写一个算法,将一个通常书写形式且书写正确的表达式转换为逆波兰式.
输入：
常规运算表达式,比如a+b
输出：
逆波兰式如 ab+
输入样例1：
A+B*(C-D)-E*F
输出样例1：
ABCD-*+EF*-
输入样例2：
b*c/d
输出样例2：
bc*d/
*/

#include <stdio.h>
#include <stdlib.h>

int priority(char op){
    if(op == '+' || op =='-'){
        return 1;
    }
    if(op == '*' || op =='/'){
        return 2;
    }
    return 0; // 括号或者其他非法字符
}

char op_stack[1000];
int top = -1;

// src数组结束标志为'\0'
void ReversePolish(char src[]){
    char c;
    for(int i=0; src[i]!='\0'; ++i){
        c = src[i];
        if((c<='Z'&&c>='A')||(c<='z'&&c>='a')){
            putchar(c); //遇到操作数直接输出，因为是叶子节点
        }else if(c=='+' || c=='-' || c== '*' || c=='/'){
            while(top>=0 && op_stack[top] != '(' &&
            priority(op_stack[top]) >= priority(c)){
                putchar(op_stack[top]);
                top--;
            }
            op_stack[++top] = c;
        }else if(c == '('){
            op_stack[++top] = c;
        }else if(c == ')'){
            while(top>=0 && op_stack[top]!='('){
                putchar(op_stack[top--]);
            }
            if(op_stack[top] == '('){
                top--; // 弹出'('
            }
        }    
    }
    // 输出栈中剩余运算符
    while(top>=0){
        putchar(op_stack[top--]);
    }
    putchar('\n');
}

int main(){
    char src[1000];
    char c;
    int i=0;
    while((c=getchar())!='\n' && c!=EOF){
        src[i]=c;
        i++;
    }
    src[i]='\0';
    ReversePolish(src);
    return 0;
}