/*
逆序列
描述：
试写一算法，识别依次读入的一个以@为结束符的字符序列是否为形如“序列1&序列2”模式的字符序列。其中序列1和序列2中都不包含字符“&”，且序列2是序列1的逆序列。
例如，“a+b&b+a”是属于该模式的字符序列，而“1+3&3-1”则不是。
输入：
输入字符序列
输出：
如果序列符合模式则输出1,不符合则输出0
输入样例1：
a+b&b+a@
输出样例1：
1
*/
#include <stdio.h>

char array[1000];

int main(void){
    int head = 0;
    int tail = 0;
    int i = 0;
    while((scanf("%c",&array[i])) && array[i]!='@'){
        ++i;
    }
    tail = i-1; //tail指向@的前一个字符
    while(head<tail){
        if(array[head]!=array[tail]){
            printf("0\n");
            return 0;
        }
        head += 1;
        tail -= 1;
    }
    
    if(array[head] == '&' && head==tail){
        printf("1\n");
    }
    return 0;
}

