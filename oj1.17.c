#include <stdio.h>

int fibnac(int k, int m);
int main(){
    int k,m;
    scanf("%d%d",&k,&m);
    printf("%d\n",fibnac(k,m));
    return 0;
}

int fibnac(int k, int m){
    int f0;
    int fm=0;
    if(k>1){
        f0=0;
    }else{
        f0=1;
    }

    if(m<k){
        if(m==k-1){
            return 1;
        }else{
            return 0;
        }
    }else{
        for(int i=1;i<=k;i++){
            fm=fm+fibnac(k,m-i);
        }
    }

    return fm;
}