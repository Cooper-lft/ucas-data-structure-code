#include <stdio.h>

typedef struct {
    int Mscore; //men score
    int Fscore; //female
    int Tscore; //total
}Score;

char currLine[5];

int my_getline(){
    char temp;
    int i=0;
    while((temp=getchar())!='\n' && temp!= EOF){
        if(temp!=' ' && temp!='\t'){
            currLine[i]=temp;
            i++;
        }
    }
    currLine[i]='\0';
    return i;
}

int my_atoi(char currLine[]){
    int score=0;
    for(int i=3;currLine[i]!='\0';i++){
        score = currLine[i]-'0' + score*10;
    }
    return score;
}

void initArray(Score array[]){
    for(int i=0;i<5;i++){
        array[i].Fscore=array[i].Mscore=array[i].Tscore=0;
    }
}

int main(void){
    char school;
    int index,score;
    Score array[5]; //index从0到4分别是从A到E
    initArray(array);
    while (my_getline())
    {
        score=my_atoi(currLine);
        school=currLine[2];
        index = school - 'A';
        if(currLine[1]=='M'){
            array[index].Mscore=array[index].Mscore + score;
        }else{
            array[index].Fscore=array[index].Fscore + score;
        }
        array[index].Tscore = array[index].Fscore + array[index].Mscore;
    }
    
    for(int i=0;i<5;i++){
        if(array[i].Mscore) printf("%c %c %d\n",'A'+i,'M',array[i].Mscore);
        if(array[i].Fscore) printf("%c %c %d\n",'A'+i,'F',array[i].Fscore);
        if(array[i].Tscore) printf("%c %d\n",'A'+i,array[i].Tscore);
    }


    return 0;
}