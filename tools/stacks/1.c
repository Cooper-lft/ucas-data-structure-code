//动态顺序栈
#define INITSIZE 100 // 栈空间初始分配量
#define INCREMENTSIZE 10 // 栈空间分配增量
#define OK 1
#define ERROR -1

typedef int ElemType;
typedef int Status;
typedef struct{
    int top; // 栈顶指针
    ElemType    *base; // 栈底指针，栈不存在时值为NULL；
    int stacksize;     // 当前已分配空间
}SqStack;

//1. 构造一个空栈S
Status InitStack(SqStack *s);
//2. 取栈的长度
int GetLen(SqStack *s);
//3. 查看栈顶元素。只查看，不修改栈
Status GetTop(SqStack *s, ElemType *e);
//4. 元素入栈
Status Push(SqStack *s,ElemType *e);
//5. (栈顶)元素出栈
Status Pop(SqStack *s,ElemType *e);
//6. 判断栈是否为空
int IsStackEmpty(SqStack *s);
//7. 遍历栈，从栈顶到栈底依次对每个元素调用visit()
Status StackTraverse(SqStack *s, visit());

Status InitStack(SqStack *s){
    s->base = (ElemType *)malloc(INITSIZE*sizeof(ElemType));
    if(!s){
        return ERROR;
    } // 即栈非空但初始化
    s->stacksize = INITSIZE;
    s->top = 0;
    return OK;
}

int GetLen(SqStack *s){
    return (s->top);
}

//只查看，不修改栈
Status  GetTop(SqStack *s,ElemType *e){
    if(s->top == 0) return ERROR; // 栈空，返回出错标志
    *e = s->base[s->top - 1];
    return OK;
}

Status Push(SqStack *s,ElemType *e){

}