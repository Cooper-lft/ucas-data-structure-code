#include <stdio.h>
int recurse(int m,int n);
int main(){
    int m,n;
    scanf("%d",&m);
    getchar();
    scanf("%d",&n);
    printf("%d\n",recurse(m,n));
    return 0;
}

int recurse(int m,int n){
    if(m==0){
        return 0;
    }else{
        return recurse(m-1,2*n)+n;
    }
}