/*
阶乘
描述
编写算法，计算i!*2^i(i=0,1,...,n-1)的值并分别存入数组a[arrsize]的各个分量中。假设
计算机中允许的正数最大值为MAXINT=(2^32)-1,则当n>arrsize或对某个k(0<=k<=n-1)
使k!*2^k>MAXINT时，应按出错处理
输入：
输入为两个数，用空格隔开，分别表示n和arrsize。其中0<n,arrsize<=20
输出：
若没有发生出错，则依次输出i!*2^i(i=0,1,...,n-1)的每个分量，用空格隔开
若发生出错，则直接输出-1.
输入样例1：
3 10
输出样例1：
1 2 8
输入样例2：
10 9
输出样例2：
-1
*/

#include <stdio.h>
#define MAXINT 0xffffffffU
#define Overflow -1
#define OK 1

int factorial(int n, int a[]);
void print(int n,int a[]);

int main(void){
    int n, arrsize;
    int IsOverflow = 0;
    scanf("%d%d",&n,&arrsize);
    if(n > arrsize){
        printf("-1\n");
        return 0;
    }

    int a[arrsize];
    a[0] = 1; // i为0时比较特殊，直接单独处理

    IsOverflow = factorial(n,a);
    if(IsOverflow != Overflow){
        print(n,a);
    }

    return 0;
}

int factorial(int n, int a[]){
    for(int i=1;i<=n-1;++i){
        if(a[i-1]>(MAXINT/(2*i))){ // 用除法判断是否超过允许的最大值
            printf("-1\n");
            return -1;
        }
        a[i] = a[i-1]*2*i;
    }
    return OK;
}

void print(int n, int a[]){
    int i=0;
    for(;i<n-1;++i){
        printf("%d ",a[i]);
    }
    printf("%d\n",a[i]);
}