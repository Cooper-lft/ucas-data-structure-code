/*
链表删除元素
描述
试写一算法，在无头节点的动态单链表上实现线性表操作DELETE(L,i)。
输入
输入包含两行，第一行是链表中的元素，第二行表示需要删除的第i个元素，i从0开始计数
若删除后，链表不包含元素，则输出“NULL”。
输出
输出删除后的链表元素
输入样例 1:
1 2 3 4 5
4
输出样例 1:
1 2 3 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 定义链表节点结构体
typedef struct Node {
    int val;
    struct Node* next;
} Node;

// 2. 创建链表（将字符串解析成链表）
Node* createList(char* str) {
    Node* head = NULL;
    Node* tail = NULL;
    
    // 使用 strtok 分割字符串（C标准库函数）
    char* token = strtok(str, " ");
    while (token != NULL) {
        int num = atoi(token);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = num;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        token = strtok(NULL, " ");
    }
    return head;
}

// 3. 核心删除函数 (DELETE(L, i))
Node* deleteNode(Node* head, int i) {
    // 链表为空 或 索引无效
    if (head == NULL || i < 0) return head;

    // --- 情况 1：删除头结点 (i == 0) ---
    if (i == 0) {
        Node* temp = head;
        head = head->next;  // 更新头指针
        free(temp);         // 释放原头结点内存
        return head;
    }

    // --- 情况 2：删除非头结点 (i > 0) ---
    Node* curr = head;
    // 找到第 i-1 个节点，即要删除节点的前驱节点
    // 注意这里循环次数是 i-1 次
    for (int j = 0; j < i - 1; j++) {
        if (curr->next == NULL) {
            // 如果 i 超出链表长度，越界，不做任何操作直接返回
            return head;
        }
        curr = curr->next;
    }

    // 检查要删除的节点是否存在
    if (curr->next != NULL) {
        Node* target = curr->next;   // 要删除的节点
        curr->next = target->next;   // 跳过 target
        free(target);                // 释放内存
    }

    return head;
}

// 4. 输出链表
void printList(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    
    Node* curr = head;
    int isFirst = 1;
    while (curr != NULL) {
        if (!isFirst) {
            printf(" ");
        }
        printf("%d", curr->val);
        isFirst = 0;
        curr = curr->next;
    }
    printf("\n");
}

// 5. 释放整个链表内存
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 定义缓冲区存储第一行输入
    char buffer[1024];
    
    // 读取第一行（链表元素）
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    // 去掉 fgets 读入的末尾换行符
    buffer[strcspn(buffer, "\n")] = 0;
    
    // 读取第二行（需要删除的下标 i）
    int i;
    if (scanf("%d", &i) != 1) {
        return 0;
    }
    
    // 创建链表
    Node* head = createList(buffer);
    
    // 执行删除操作
    head = deleteNode(head, i);
    
    // 输出结果
    printList(head);
    
    // 释放内存（好的编程习惯）
    freeList(head);
    
    return 0;
}