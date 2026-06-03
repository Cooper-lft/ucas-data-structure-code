/*
双向循环链表访问
描述：
设有一双向循环链表，每个节点中除有prior,data和next三个域外，还增设了一个访问频度域freq。在链表被启用之前，频度域freq的值均初始化为0，
而每当对链表进行一次LOCATE(L,x)的操作后，被访问的节点（即元素值等于x的节点）中的频度域freq的值便增1，
同时调整链表中节点之间的次序，使其按访问频度非递增的次序顺序排列，以便始终保持被频繁访问的节点总是靠近表头结点。
编写符合上述要求的LOCATE操作的算法。
输入：
输入包含三行，第一行是链表中的元素个数，
第二行是链表中的元素，第三行包含所有被访问的元素
输出：
顺序输出从表头节点开始的链表中的元素。
注意：如果有多个元素的访问次数相同，需要按照访问次序，将先访问到的元素放在前面
输入样例1：
10
1 2 3 4 5 6 7 8 9 10
1 2 2 2 3 4 5 5 4 10 9
输出样例1：
2 4 5 1 3 10 9 6 7 8
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    int freq;
    struct LNode* prior;
    struct LNode* next;
    int order; // 用于标记访问次序的先后
}LNode;

// 采用带有头节点的链表
LNode* CreateList(LNode* head,int lenth){
    LNode* curr;
    LNode* newNode; 
    int value;
    head->prior = head;
    head->next = head;  // 双向链表的头节点开始时前驱和后继都是自己
    head->freq = 0;
    curr = head;
    for(int i=0;i<lenth;++i){
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        scanf("%d",&value);
        newNode->data = value;
        newNode->freq = 0;
        newNode->next = head;
        newNode->prior = curr;
        curr->next = newNode;
        head->prior = newNode; // 头节点的前驱是尾结点，因为是双向循环链表
        curr = newNode; // curr 往前推进
    }
    return head;
}

LNode* SortList(LNode* head, int length){
    LNode* curr,* next_ptr,* prior_ptr;
    for(int i=1; i<length; ++i){
        curr = head->next->next; // 从第二个节点开始（除开头节点后）
        for(int j=0;j<length-i;++j){
            next_ptr = curr->next;
            prior_ptr = curr->prior;
            if(curr->freq > prior_ptr->freq ||
            (curr->freq == prior_ptr->freq && curr->order < prior_ptr->order)){
                prior_ptr->prior->next = curr;
                curr->prior = prior_ptr->prior;

                curr->next = prior_ptr;
                prior_ptr->prior = curr;

                prior_ptr->next = next_ptr;
                next_ptr->prior = prior_ptr;
            }
            curr = curr->next;
        }
    } // 冒泡排序
    return head;
}

LNode* Locate(LNode* head, int x){
    LNode* next_ptr,* prior_ptr;
    LNode* curr = head->next;
    int length = 0;
    static int order = 1; //访问次序,注意只能初始化1次，不然每次调用都重新记录
    while(curr!=head){
        length++;
        curr = curr->next;
    }// 获取链表长度
    
    curr = head->next;
    while(curr!=head && curr->data!=x){
        curr = curr->next;
    }
    if(curr!=head){
        if(curr->freq == 0){ //说明之前没有访问过，所以增加一个访问次序
            curr->order = order;
            order++;
        }
        curr->freq += 1;
        head = SortList(head, length);
    }
    return head;
}

void print(LNode* head){ // 考虑头节点
    LNode* curr = head->next;
    while(curr->next!=head){
        printf("%d ",curr->data);
        curr = curr->next;
    }
    printf("%d\n",curr->data);
}

int main(void){
    LNode* head = (LNode*)malloc(sizeof(LNode));
    int n;
    scanf("%d",&n);
    head = CreateList(head,n);

    char separator;
    int num;
    while(1){
        scanf("%d%c",&num,&separator);
        head = Locate(head, num);
        if(separator!=' '){
            break;
        }
    }
    print(head);
    return 0;
}

