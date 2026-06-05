#include <stdio.h>
#define State int
#define Found 1
#define NotFound -1

int board [8][8]; // 棋盘,棋盘上结点值表示是第几步到达的

typedef struct Node{
    int x;  // 横坐标，从0到7，下同
    int y;  // 纵坐标
    int direction;  // 下一步方位，从0到7(初始为0？)
}Node;

Node step_stack [64]; // 记录步数的栈
int top = -1; // 栈顶指针
int step = 0; // 记录步数，当step为64时说明走完棋盘

void InitBoard(){ // 初始化棋盘，每个点位都是0
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            board[i][j] = 0;
        }
    }
}

void PrintBoard(){
    printf(" ");
    for(int i=0;i*3<24;i++){
        printf("%3d",i);
    }
    printf("\n"); // 打印横坐标0-7
    
    printf(" ");
    for(int count=0;count<25;count++){
        printf("-");
    }
    printf("\n"); // 打印顶横线
    
    for(int i=0;i<8;i++){
        printf("%d",i);
        for(int j=0;j<8;j++){
            printf("|%2d",board[i][j]);
        }
    printf("|\n");
    
    printf(" ");
    for(int count=0;count<25;count++){
        printf("-");
    }
    printf("\n");
    }
    printf(" ");
    for(int i=0;i*3<24;i++){
        printf("%3d",i);
    }
    printf("\n"); // 打印底横线
}

int offsetX[8] = {-2,-1,1,2,2,1,-1,-2}; // 按照下一步方位从0到7，对应X方向的偏移量
int offsetY[8] = {1,2,2,1,-1,-2,-2,-1};

// 弹栈只需要top-=1就好了,同时要维护step值，即step-=1。
// 获取栈顶结点
Node GettopNode(Node step_stack[]){
    if(top>=0){
        return step_stack[top];
    }else{
        printf("stack is empty\n");
        Node empty={0,0,0};
        return empty;
    }
}
 


// 下一步要走的点位合法（不越界且先前未走过）
int IsValidDirect(int nextNodeX, int nextNodeY){
    if(nextNodeX>=0 && nextNodeX <= 7 && nextNodeY>=0 && nextNodeY<=7 
        && board[nextNodeX][nextNodeY] == 0){
        return 1;
    }else return 0;
}

// 计算从当前点位出发可以走的分支个数
int CountBranch(int currNodeX, int currNodeY){
    int count = 0;
    for(int i=0;i<8;i++){
        int nextNodeX = currNodeX + offsetX[i];
        int nextNodeY = currNodeY + offsetY[i];
        if(IsValidDirect(nextNodeX,nextNodeY)){
            count++;
        }
    }
    return count;
}

// 核心函数:深度优先，失败回溯，尝试走完棋盘
State KnightTour(Node currNode){
    Node nextNode;
    while(top>=0){
        nextNode.direction = 0;
        nextNode.x = currNode.x + offsetX[currNode.direction];
        nextNode.y = currNode.y + offsetY[currNode.direction];
        if(IsValidDirect(nextNode.x,nextNode.y)){
            top++;
            step++;
            currNode = nextNode; 
            step_stack[top] = currNode;  // 走下一步
            board[currNode.x][currNode.y] = step;
        }else{
            step_stack[top].direction++;
            currNode = step_stack[top]; //  更新当前所在点位的方位，继续尝试
        }
        if(step == 64){
            return Found;
        }
        
        if(step_stack[top].direction>7){  // 说明当前所在点位走不下去了，要回溯
            board[currNode.x][currNode.y] = 0;
            top--;
            step--;
            currNode = GettopNode(step_stack); // 回溯到上一步
            currNode.direction += 1; // 尝试下一个方向
            step_stack[top] = currNode; // 更新在栈中的记录
        }

    }
    if(top<0){
        printf("没有满足条件的解\n");
        return NotFound;
    }
}



int main(){
    Node currNode;
    currNode.direction = 0;
    InitBoard();

    while(1){
        printf("请先后输入初始位置的横坐标和纵坐标（从0到7）:\n");
        scanf("%d%d",&currNode.x,&currNode.y);
        if(currNode.x<0 || currNode.x >7 || currNode.y<0 || currNode.y>7){
            printf("输入坐标有误，请重新输入：");
        }else{
            break;
        }
    }
    step++;
    top++;
    board[currNode.x][currNode.y] = step;
    step_stack[top] = currNode;

    KnightTour(currNode);

    PrintBoard();
    return 0;
}