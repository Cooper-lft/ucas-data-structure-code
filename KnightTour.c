#include <stdio.h>
#define State int
#define Found 1
#define NotFound -1

int board [8][8]; // 棋盘,棋盘上结点值表示是第几步到达的

typedef struct Node{
    int x;  // 横坐标，从0到7，下同
    int y;  // 纵坐标
    int tried;  // 已经尝试了nextNode的数量,最大为8
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

// 收集当前节点所有合法的下一步，并按照在nextNode处，进一步可能的分支数
// 从小到大排序
// 参数是当前节点横纵坐标和当前节点的下一节点的待选数组(元素是方向的取值，0到7)
// 返回值是待选数组中的节点个数
int CollectAndSort(int currNodeX,int currNodeY, int candidates[8]){
    Node nextNode;
    int count = 0;
    // 遍历方向0-7，找出合法方向并收集，记录合法方向个数count
    for(int direction=0; direction<8; direction++){
        nextNode.x = currNodeX + offsetX[direction];
        nextNode.y = currNodeY + offsetY[direction];
        if(IsValidDirect(nextNode.x,nextNode.y)){
            candidates[count] = direction; // 待选数组中存放合法方向 
            count++;
        }
    }
    // 冒泡排序，nextNode处的可能分支数从小到大
    for(int i=0; i < count; i++){
        for(int j = 0;j<count-1-i;j++){
            int temp;
            int nextNodeX_j = currNodeX + offsetX[candidates[j]];
            int nextNodeY_j = currNodeY + offsetY[candidates[j]];
            int nextNodeX_j_1 = currNodeX + offsetX[candidates[j+1]];
            int nextNodeY_j_1 = currNodeY + offsetY[candidates[j+1]];
            int branch_j = CountBranch(nextNodeX_j,nextNodeY_j);
            int branch_j_1 = CountBranch(nextNodeX_j_1,nextNodeY_j_1);
            if(branch_j > branch_j_1){
                temp = candidates[j];
                candidates[j] = candidates[j+1];
                candidates[j+1] = temp;
            }
        }
    }
    return count;
}

// 核心函数:深度优先，失败回溯，尝试走完棋盘
State KnightTour(Node startNode){
    Node nextNode,currNode;
    startNode.tried = 0;
    top = 0;
    step = 1;
    board[startNode.x][startNode.y] = step;
    step_stack[top] = startNode;

    while(top>=0){
        currNode = step_stack[top];
        
        if(step == 64){
            return Found;
        }
        int candidates[8]; 
        int cand_count = CollectAndSort(currNode.x,currNode.y,candidates);

        if(currNode.tried < cand_count){ // 还有未尝试的方向
            int next_dir = candidates[currNode.tried]; // 本次要尝试的方向
            step_stack[top].tried++;
            currNode = step_stack[top];

            nextNode.x = currNode.x + offsetX[next_dir];
            nextNode.y = currNode.y + offsetY[next_dir];
            nextNode.tried = 0;
            top++;
            step++;
            step_stack[top] = nextNode;  // 走下一步
            board[nextNode.x][nextNode.y] = step;
        }else{
            // 说明当前所在点位走不下去了，要回溯
            board[currNode.x][currNode.y] = 0;
            step--;
            top--;
        }
    }
    if(top<0){
        printf("没有满足条件的解\n");
        return NotFound;
    }
}



int main(){
    Node startNode;
    InitBoard();

    while(1){
        printf("请先后输入初始位置的横坐标和纵坐标（从0到7）:\n");
        scanf("%d%d",&startNode.x,&startNode.y);
        if(startNode.x<0 || startNode.x >7 || startNode.y<0 || startNode.y>7){
            printf("输入坐标有误，请重新输入：");
        }else{
            break;
        }
    }

    KnightTour(startNode);

    PrintBoard();
    return 0;
}