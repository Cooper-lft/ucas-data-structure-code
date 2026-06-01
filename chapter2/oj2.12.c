#include <stdio.h>
#include <ctype.h>
#define MAXLEN 100

int A[MAXLEN];
int B[MAXLEN];

int main(){
    int c;
    int i=0;
    while((c=getchar())!=EOF){
        if(isalpha(c)){
            A[i]=c;
            i++;
        }
        if(c=='\n') break;
    }//构建A表,i为A表元素个数

    int j=0;
    while((c=getchar())!=EOF){
        if(isalpha(c)){
            B[j]=c;
            j++;
        }
        if(c=='\n') break;
    }

    int k=0;
    for(;k<i&&k<j&&A[k]==B[k];k++){
        ;
    }//跳过相同的前缀

    if(k==i&&k==j){
        printf("0");
    }else if(k==i){
        printf("1");
    }else if(k==j){
        printf("2");
    }else{
        if((A[k]-B[k])<0){
            printf("1");
        }else{
            printf("2");
        }
    }

    return 0;
}