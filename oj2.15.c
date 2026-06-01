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
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode{
    int data;
    struct Lnode *next;
}Lnode,LinkedList; //链表节点和头节点类型声明

LinkedList* CreatList_L(int n,int arr[]);

int main(){


    return 0;
}

//创建单链表,数据由arr[]数组给出
//参数n是链表长度，包含头节点
LinkedList* CreatList_L(int n, int arr[]){
    LinkedList* L;
    Lnode* p;
    
    L = (LinkedList*)malloc(sizeof(Lnode));
    L->data = n; //头节点的数据存放链表长度
    L->next = NULL;  // 初始化一个带有头节点的空链表

    p = (Lnode*)malloc(sizeof(Lnode)); // 工作指针


    return L ;
}