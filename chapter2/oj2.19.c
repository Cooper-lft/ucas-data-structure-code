/*
链表删除指定范围的元素
描述

已知线性表中的元素以递增有序排列，并以单链表为存储结构。试写一高效算法，删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删节点的空间。

注意：mink和maxk是给定的两个参变量，他们的值可以和表中的元素相同，也可以不同。


输入

输入包含两行，第一行是链表中的元素，以空格分隔。

第二行分别为mink和maxk两个元素，以空格分隔。


输出

输出最后的链表中的元素
输入样例 1:
1 2 3 4 5 8 12 15 16 22
6 18
输出样例 1:
1 2 3 4 5 22
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode* next;
}LNode;

LNode * InsertList(LNode* head, int value){
    LNode* curr,*temp_ptr;
    temp_ptr = (LNode*)malloc(sizeof(LNode));
    temp_ptr->data = value;
    temp_ptr->next = NULL; // temp_ptr是工作指针
    if(head == NULL){
        head = temp_ptr;
    }else{
        curr = head;
        while(curr->next!=NULL){
            curr = curr->next;
        }
        curr->next = temp_ptr;
    }
    return head;
}

LNode* Delete(LNode* head, int mink, int maxk) {
    // 哨兵节点，next 指向真实头节点，方便处理头节点可能被删的情况
    LNode dummy;
    dummy.next = head;
    LNode *prev = &dummy;   // 指向待删除区间前一个节点
    LNode *curr = head;     // 当前检查的节点

    // 1. 找到第一个值 > mink 的节点，prev 为其前驱
    while (curr != NULL && curr->data <= mink) {
        prev = curr;
        curr = curr->next;
    }

    // 2. 删除所有值 < maxk 的节点（即大于 mink 且小于 maxk 的区间）
    while (curr != NULL && curr->data < maxk) {
        LNode *temp = curr;
        curr = curr->next;
        free(temp);
    }

    // 3. 将前驱与剩余链表连接
    prev->next = curr;

    // 返回新的头节点（哨兵节点的 next 可能因头节点被删而改变）
    return dummy.next;
}

void print(LNode* head){
    LNode* curr = head;
    if(curr == NULL){
        printf("ERROR");
    }else{
        while(curr->next!=NULL){
            printf("%d ",curr->data);
            curr = curr->next;
        }
        printf("%d",curr->data);
        printf("\n");
    }
}

int main(void){
    LNode* head = NULL;
    int value,mink,maxk;
    char c;
    scanf("%d%c",&value,&c);
    while(c==' '){
        head = InsertList(head,value);
        scanf("%d%c",&value,&c);
    }
    head = InsertList(head,value);

    scanf("%d%d",&mink,&maxk);
    head = Delete(head, mink, maxk);

    print(head);

    return 0;
}