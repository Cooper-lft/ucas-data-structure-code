/*
括号配对
描述：
试写一个判别表达式中开,闭括号是否配对出现的算法。
比如:'(a+b(c-d))'是配对出现的,而'(d-e))'不是配对出现的。
输入：
表达式,如:'a+b(c-d)’
输出：
表达式中的括号是否配对出现,是则输出1,否则输出0
输入样例1：
(a+b(c-d))
输出样例1：
1
*/

#include <stdio.h>
#define State int 
#define Pair 1
#define NotPair 0
char array[1000];

State Check(char array[], int i);

int main(){
    char c;
    int i=0;
    while((c=getchar())!='\n' && c!=EOF){
        array[i] = c;
        i++;
    }
    /*
    int head = 0;
    int tail = i-1;
    */
    printf("%d\n",Check(array,i));

    return 0;
}

State Check(char array[],int i){
    int count = 0;
    for(int j=0;j<i;j++){
        if(array[j]=='('){
            count++;
        }
        if(array[j]==')'){
            count--;
        }
    }
    if(count == 0){
        return Pair;
    }else{
        return NotPair;
    }
}