#include <stdio.h>

void print();

int main(){
    print();
    return 0;
}

void print(){
    int array[3];
    int temp;
    scanf("%d%d%d",&array[0],&array[1],&array[2]);
    for(int j=0;j<2;j++){
        for(int i=0;i<2-j;i++){
            if(array[i]<array[i+1]){
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
            }
        }    
    }
    
    //冒泡排序后从第一个元素开始从大到小打印数据
    for(int i=0;i<3;i++){
        printf("%d ",array[i]);
    }
    printf("/n");
}
