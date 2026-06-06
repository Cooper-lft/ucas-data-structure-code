# 马踏棋盘（Knight's Tour）—— C 语言实现

## 运行环境

- **操作系统**：WSL2 Ubuntu 22.04
- **编译器**：GCC（GNU Compiler Collection）

## 编译与运行

```bash
# 编译
gcc -o KnightTour KnightTour.c

# 运行
./KnightTour
```

编译选项说明：
- `-o KnightTour`：指定输出可执行文件名为 `KnightTour`
- 如需开启警告和调试信息，可使用 `gcc -Wall -g -o KnightTour KnightTour.c`

---

## 数据结构与作用

### 1. 棋盘 `board[8][8]`

```c
int board[8][8];
```

- **类型**：8×8 的 `int` 二维数组
- **作用**：记录马踏棋盘的路径，`board[x][y]` 的值表示第几步到达该位置。值为 `0` 表示该位置尚未被访问。

### 2. 结点结构体 `Node`

```c
typedef struct Node {
    int x;      // 横坐标（0 ~ 7）
    int y;      // 纵坐标（0 ~ 7）
    int tried;  // 已尝试的下一方向数量（最多 8 个）
} Node;
```

- **作用**：封装棋盘上一个位置的状态信息。`tried` 字段用于回溯时记录当前结点已经尝试了多少个候选方向，避免重复尝试。

### 3. 路径栈 `step_stack[64]`

```c
Node step_stack[64];
int top = -1;   // 栈顶指针
int step = 0;   // 当前步数（0 ~ 64）
```

- **作用**：用数组模拟栈，存储当前搜索路径上每一步的结点信息。当 `step == 64` 时表示已成功走完整个棋盘。`top` 为栈顶指针，配合 `step` 实现入栈/出栈（前进/回溯）操作。

### 4. 方向偏移数组 `offsetX[8]` / `offsetY[8]`

```c
int offsetX[8] = {-2, -1,  1,  2,  2,  1, -1, -2};
int offsetY[8] = { 1,  2,  2,  1, -1, -2, -2, -1};
```

- **作用**：定义马（Knight）在国际象棋中的 8 种合法走法。方向 `0~7` 分别对应"马走日"的 8 个方向，按顺时针排列。当前坐标 `(x, y)` 沿方向 `d` 移动后的新坐标为 `(x + offsetX[d], y + offsetY[d])`。

### 5. 状态常量

```c
#define State  int
#define Found  1
#define NotFound  -1
```

- **作用**：定义搜索返回值语义，`Found`（1）表示找到解，`NotFound`（-1）表示无解。

---

## 函数声明与作用

| 函数 | 声明 | 作用 |
|------|------|------|
| `InitBoard` | `void InitBoard()` | 初始化棋盘，将所有位置置为 `0`（未访问） |
| `PrintBoard` | `void PrintBoard()` | 按网格格式打印棋盘，显示每个位置是第几步到达，带有行列坐标标尺 |
| `IsValidDirect` | `int IsValidDirect(int nextNodeX, int nextNodeY)` | 判断下一步位置 `(nextNodeX, nextNodeY)` 是否合法（不越界且未被访问过），返回 `1` 合法 / `0` 非法 |
| `CountBranch` | `int CountBranch(int currNodeX, int currNodeY)` | 计算从当前位置 `(currNodeX, currNodeY)` 出发，有多少个合法分支（即可走的下一位置数） |
| `CollectAndSort` | `int CollectAndSort(int currNodeX, int currNodeY, int candidates[8])` | 收集当前位置所有合法方向存入 `candidates` 数组，并**按各方向下一步的分支数从小到大排序**（Warnsdorff 启发式规则），返回候选方向个数 |
| `KnightTour` | `State KnightTour(Node startNode)` | 核心搜索函数，使用 DFS + 回溯 + Warnsdorff 启发式策略求解马踏棋盘问题，返回 `Found` 或 `NotFound` |
| `main` | `int main()` | 程序入口：初始化棋盘 → 读取用户输入的起始坐标 → 调用 `KnightTour` 搜索 → 打印结果棋盘 |

---

## 核心思想与启发式算法提速

### 问题描述

马踏棋盘问题（Knight's Tour Problem）：在国际象棋 8×8 棋盘上，马从任意起点出发，按照"马走日"的规则移动，要求不重复地访问棋盘上全部 64 个格子，找出一条合法路径。

### 核心思想：深度优先搜索（DFS）+ 回溯

程序采用**栈**模拟 DFS 递归过程：

1. 将起点坐标压入栈 `step_stack`，标记棋盘。
2. 在每一步，收集当前结点的所有合法下一步方向，按启发式规则排序后依次尝试。
3. 若当前方向可行，则前进（入栈），`step` 加 1；若所有方向均已尝试且无法继续，则回溯（出栈），撤销棋盘标记，`step` 减 1。
4. 当 `step == 64` 时，找到解；当栈空（`top < 0`）时，无解。

### 启发式算法提速：Warnsdorff 规则

暴力 DFS 搜索 8×8 棋盘的理论分支数高达 $8^{64}$，直接穷举完全不现实。程序使用 **Warnsdorff 启发式规则**大幅剪枝：

> **优先选择下一步可走分支数最少的方向。**

#### 原理

- 分支数少的位置意味着"死胡同风险高"——如果不尽早访问，后续可能无路可走。
- 优先走"冷门"位置，将"热门"（分支多、选择多）的位置留给后面，能显著减少回溯次数。

#### 实现（`CollectAndSort` 函数）

1. 遍历 8 个方向，收集所有合法的下一步方向到 `candidates`。
2. 对每个候选方向，调用 `CountBranch` 计算从该候选位置出发的合法分支数。
3. 用冒泡排序将 `candidates` 按分支数**从小到大**排列。
4. `KnightTour` 按此排序依次尝试各方向——总是先走分支最少的。

#### 效果

- 朴素 DFS：在 8×8 棋盘上基本不可行，耗时指数级增长。
- Warnsdorff 启发式：对于绝大多数起始位置，算法几乎无需回溯即可在几千步内找到解，将不可解问题变为**秒级求解**。

---

## 程序结构总览

```
KnightTour.c
├── 宏定义 / 常量：Found, NotFound, 方向偏移数组
├── 数据结构：Node（结点）, step_stack（栈）, board（棋盘）
├── InitBoard()          —— 棋盘初始化
├── PrintBoard()         —— 棋盘打印
├── IsValidDirect()      —— 合法性判断
├── CountBranch()        —— 分支计数
├── CollectAndSort()     —— 启发式排序（Warnsdorff 规则）
├── KnightTour()         —— DFS + 回溯核心算法
└── main()               —— 入口，交互输入输出
```
