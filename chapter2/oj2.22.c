/*
链表就地逆置
描述
试写一算法，实现单链表的就地逆置
输入
输入为给定链表的所有元素，以逗号分隔
输出
输出为链表逆置后的结果，以逗号分隔
输入样例 1:
s,a,s,f,w,s,a,d,a,S
输出样例 1:
S,a,d,a,s,w,f,s,a,s
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    char data;
    struct LNode* next;
}LNode,*LinkList;

LNode* InsertList(LNode* head, int value){
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

LNode* ReverseList(LNode* head){
    LNode* pre,*curr,*next;
    pre = NULL; // 前驱
    curr = head;
    next = NULL; // 后继

    while(curr != NULL){
        next = curr->next;  // 保存下一个节点
        curr->next = pre;   // 当前节点反向
        pre = curr;         // 前驱后移
        curr = next;        // 当前指针后移
    }

    return pre;
}

void printList(LNode* head){
    LNode* curr = head;
    if(curr == NULL){
        printf("ERROR");
    }else{
        while(curr->next!=NULL){
            printf("%c,",curr->data);
            curr = curr->next;
        }
        printf("%c",curr->data);
        printf("\n");
    }
}

int main(){
    LNode* head = NULL;
    char data,separator;
    while(1){
        scanf("%c%c",&data,&separator);
        head = InsertList(head,data);
        if(separator == '\n'){
            break;
        }
    }
    head = ReverseList(head);
    printList(head);
    return 0;
}