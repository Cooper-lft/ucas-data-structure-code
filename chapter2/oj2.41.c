/*
稀疏多项式求导
描述：
试以循环链表作稀疏多项式的存储结构，编写求其导函数的算法，
要求利用原多项式中的节点空间存放其导函数（多项式），同时释放所有无用（被删）节点。
稀疏多项式中采用的循环链表存储结构LinkedPoly定义为：
typedef struct PolyNode{
  PolyTerm data;
  Struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;
输入：
输入为给定的多项式
输出：
输出为求导之后的结果，按照多项式中每一项的幂次由高到低排列
如果导数为0，则输出0
输入样例1：
- 2x + 4x^2 + 2x^3 + 3x^3 + 2x + 3x^2 - 3x^10
输出样例1：
- 30x^9 + 15x^2 + 14x
输入样例2：
3x^2 + 4
输出样例2：
6x
*/

#include <stdio.h>
#include <stdlib.h>
#define PolyTerm int

typedef struct PolyNode{
  PolyTerm data;
  struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;
