// 链表合并
/*
描述：
已知指针ha和hb分别指向两个单链表的头结点，并且已知两个链表的长度分别为m和n。
试写一算法将这两个链表连接在一起（即令其中一个表的首元节点连在另一个表的最后一个节点之后），
假设指针hc指向连接后的链表的头结点，并要求算法以尽可能短的时间完成链接运算。
输入：
输入包括三行，第一行是两个链表的长度m和n，第二行和第三行分别为链表ha和hb中的元素，以空格分隔。
输出：
输出合并后的链表hc，元素以空格分隔
输入样例：
5 3
1 2 3 4 5
1 2 3
输出样例：
1 2 3 1 2 3 4 5
看样子是让ha插在hb后面
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode{
    int data;
    struct Lnode *next;
}Lnode, *LinkList; // 链表节点和头节点类型声明

LinkList InitList(){ // 初始化，返回链表头节点
    LinkList head = (Lnode*)malloc(sizeof(Lnode));
    head->next = NULL;
    return head;
}

Lnode* InsertList(Lnode* tail, int value){ // 在链表尾部插入结点，并维护尾结点
    Lnode *newNode;
    newNode = (Lnode*)malloc(sizeof(Lnode));
    tail->next = newNode;
    newNode->data = value;
    newNode->next = NULL;
    tail = newNode;
    return tail;
}

int main(){
    int lenth_a,lenth_b,value;
    
    scanf("%d %d", &lenth_a, &lenth_b);
    
    LinkList ha,hb,hc;
    Lnode* tail_a,* tail_b;
    
    ha = InitList();
    hb = InitList();

    tail_a = ha;
    tail_b = hb;

    for(int count = 1; count <= lenth_a; count++){ // 构建ha链表
        scanf("%d",&value);
        tail_a = InsertList(tail_a, value);
    }

    for(int count = 1; count <= lenth_b; count++){ // 构建hb链表
        scanf("%d",&value);
        tail_b = InsertList(tail_b, value);
    }

    hc = hb;
    tail_b->next = ha->next; // ha 尾与hb首元节点相连，hc头节点就是ha头节点

    Lnode* work_ptr = hc->next;
    while(work_ptr != NULL){
        printf("%d",work_ptr->data);
        if(work_ptr->next != NULL){
            printf(" ");
        }
        work_ptr = work_ptr->next;
    }
    printf("\n");

    return 0;
}
