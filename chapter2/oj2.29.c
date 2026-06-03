/*
修改链表
描述：
已知A，B和C为三个递增有序的线性表，现要求对A表做如下操作：
删去那些既在B表中出现又在C表中出现的元素。试对顺序表编写实现上述操作的算法
输入：
输入包含三行，分别为ABC三个线性表中的元素，以逗号分隔
输出：
输出操作之后的A表中的元素
输入样例1：
a,b,c,d,e,f,g
b,e,g,h,h
c,e,g,h
输出样例1：
a,b,c,d,f
*/
#include <stdio.h>
#include <stdlib.h>
#define Found   1
#define NotFount 0

typedef struct LNode{
    char data;
    struct LNode* next;
}LNode;

int Search(char value, LNode* head){ // 这里的链表是带有头节点的链表
    LNode* curr = head->next;
    while(curr!=NULL && curr->data != value){
        curr = curr->next;
    }
    if(curr!=NULL){
        return Found;
    }else{
        return NotFount;
    }
}

LNode* Delete(char value, LNode* head){ // 这里的head是头节点，头节点的next才是第一个有效的节点
    LNode* pre,*curr;
    pre = head;
    curr = pre->next;
    while(curr!=NULL && curr->data!=value){
        pre = curr;
        curr = curr->next;
    }
    if(curr!=NULL){
        pre->next = curr->next;
        free(curr);
    }
    return head;
}

void print(LNode* head){
    LNode* curr = head->next;
    while(curr->next!=NULL){
        printf("%c,",curr->data);
        curr = curr->next;
    }
    printf("%c\n",curr->data);
}

LNode* CreateList(LNode* head){
    char value, separator;    
    LNode* curr = head;  // curr初始指向头节点

    while(1){ 
        scanf("%c%c",&value,&separator);
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        newNode->data = value;
        newNode->next = NULL;
        curr->next = newNode;
        curr = newNode;

        if(separator!=','){
            break;
        }
    }
    return head;
}

int main (void){
    LNode* ha, *hb, *hc;
    ha = (LNode*)malloc(sizeof(LNode));
    hb = (LNode*)malloc(sizeof(LNode));
    hc = (LNode*)malloc(sizeof(LNode));
    ha->next = NULL;
    hb->next = NULL;
    hc->next = NULL;

    ha = CreateList(ha);
    hb = CreateList(hb);
    hc = CreateList(hc);

    LNode* curr, *next;
    char value;
    int InB = 0;
    int InC = 0;
    for(curr = ha->next;curr!=NULL;curr = next){
        value = curr->data;
        InB = Search(value,hb);
        InC = Search(value,hc);
        if(InB == 1 && InC == 1){
            next = curr->next;       // 先保存下一个节点
            ha = Delete(value, ha);  // 再删除当前节点
            InB = InC = 0;           // 注意标志位复位
        } else {
            next = curr->next;       // 不删除时正常移动到下一个
        }
    }

    print(ha);
    return 0;
}

