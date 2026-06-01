#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int my_getline(int s[]);

int main(){
    int x0,n;
    scanf("%d%d",&x0,&n);
    
    int *a=(int *)malloc((n+1)*sizeof(int)); //开辟空间存系数
    for(int i=0;i<=n;i++){
        scanf("%d",&a[i]);
    }//存系数

    int sum=0;
    for(int j=n;j>=0;j--){
        sum=sum*x0+a[j];
    }

    printf("%d\n",sum);

    return 0;
}

int my_getline(int s[]){
    int i=0;
    char temp;
    while((temp=getchar())!='\n'&&temp!=EOF){
        if(isalpha(temp)){
            s[i]=temp;
            i++;
        }
    }
    return i;
}