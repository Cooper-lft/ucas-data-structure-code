#include <stdio.h>
#include <ctype.h>
#define MAXLEN 101
void cpyarray(int List[],int i,int len);
int List[MAXLEN];
int len=0;
int main(){
    int c;
    while((c=getchar())!='\n'&&c!=EOF){
        List[len]=0;
        if(isdigit(c)){
            List[len]+=c-'0';
            while(isdigit(c=getchar())){
                List[len]=List[len]*10+c-'0';
            }
            len++;
            if(c=='\n') break;
        }
    }

    int x=0;
    int i=0;
    
    while(!isdigit(c=getchar())&&c!=EOF);

    if(isdigit(c)){
        x=c-'0';
        while(isdigit(c=getchar())){
            x=x*10+c-'0';
        }
    }

    for(;i<len&&x>List[i];i++){
        ;
    }//x位于index==i处

    cpyarray(List,i,len);
    List[i]=x;
    for (int i = 0; i < len+1; i++)
    {
        printf("%d ",List[i]);
    }
    printf("\n");
    return 0;
}

void cpyarray(int List[],int i,int len){
    for(int j=len-1;j>=i;j--){
        List[j+1]=List[j];
    }
}