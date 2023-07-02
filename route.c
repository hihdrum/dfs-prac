#include <stdio.h>

//#define DEBUG

#ifdef DEBUG
#define LOG(fmt, ...) printf("DBG :%s:%3d: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif


/* 共通 */
/*-----------------------------------------------*/
#define DEF_NODE_NUM (7)

/* 0 : 未接続, 1 : 接続 */
int edgeInfo[DEF_NODE_NUM][DEF_NODE_NUM] ={
  {0, 1, 1, 0, 0, 0, 1}, /* R0-RX間の接続 */
  {1, 0, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 0, 0, 0},
  {0, 0, 1, 0, 1, 1, 0},
  {0, 0, 0, 1, 0, 0, 1},
  {0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 1, 1, 0}
};

/* 接続関係にあれば、1を、なければ、0を返す。*/
int isConnect(int srcIndex, int dstIndex)
{
  return edgeInfo[srcIndex][dstIndex];
}

/* 深さ優先探索向け */
struct stack
{
  int num;
  int array[10];
};

struct pathInfo
{
  int goalNode;
  struct stack *stack;
};

void printConnection(void);
void searchNextDepth(int nextNode, struct pathInfo *pathInfo);

/* スタック関係 */
void stack_push(int i, struct stack *stack)
{
  int *num = &stack->num;
  stack->array[*num] = i;
  (*num)++;
}

void stack_pop(struct stack *stack)
{
  if(0 >= stack->num)
  {
    return;
  }

  (stack->num)--;
}

int stack_isMember(int data, struct stack *stack)
{
  for(int i = 0; i < stack->num; i++)
  {
    if(stack->array[i] == data)
    {
      return 1;
    }
  }

  return 0;
}

int stack_getLast(struct stack *stack)
{
  return stack->array[stack->num - 1];
}

/* pathInfo関係 */
int isGoal(int nodeIndex, struct pathInfo *pathInfo)
{
  return nodeIndex == pathInfo->goalNode;
}

void pushNode(struct pathInfo *pi, int node)
{
  stack_push(node, pi->stack);
}

void popNode(struct pathInfo *pi)
{
  stack_pop(pi->stack);
}

int passedNode(int node, struct pathInfo *pi)
{
  return stack_isMember(node, pi->stack);
}

void printPath(struct pathInfo *pi)
{
  struct stack *stack = pi->stack;

  for(int i = 0; i < stack->num; i++)
  {
    printf("%d ", stack->array[i]);
  }

  printf("%d", pi->goalNode);
}

void printPathInfo(struct pathInfo *pi)
{
  struct stack *stack = pi->stack;
  printf("%d - %d : %d : ", stack->array[0], pi->goalNode, stack->num);
  printPath(pi);
  putchar('\n');
}

void searchPath(struct pathInfo *pathInfo)
{
  int currentNode = stack_getLast(pathInfo->stack);
  LOG("currentNode = %d, goalNode = %d\n", currentNode, pathInfo->goalNode);

  int nextNode;
  for(nextNode = 0; nextNode < DEF_NODE_NUM; nextNode++)
  {
    if(isConnect(currentNode, nextNode))
    {
      if(isGoal(nextNode, pathInfo))
      {
        printPathInfo(pathInfo);
        continue;
      }

      if(passedNode(nextNode, pathInfo))
      {
        continue;
      }

      /* 別ノードを経由した場合の可能性を調べる。*/
      LOG("nextNode = %d, goalNode = %d\n", nextNode, pathInfo->goalNode);
      searchNextDepth(nextNode, pathInfo);
    }
  }
}

void searchNextDepth(int nextNode, struct pathInfo *pathInfo)
{
  pushNode(pathInfo, nextNode);
  searchPath(pathInfo);
  popNode(pathInfo);
}

void runDFSearch(int startNode, int goalNode)
{
  if(startNode == goalNode)
  {
    return;
  }

  struct stack stack = { .num = 0 };
  struct pathInfo pathInfo = { .goalNode = goalNode, .stack = &stack };
  searchNextDepth(startNode, &pathInfo);
}

int main(void)
{
  for(int i = 0; i < DEF_NODE_NUM; i++)
    for(int j = 0; j < DEF_NODE_NUM; j++)
    {
      runDFSearch(i, j);
    }

  return 0;
}

void printConnection(void)
{
  int src;
  for(src = 0; src < 6; src++)
  {
    int dst;
    for(dst = 0; dst < 6; dst++)
    {
      if(isConnect(src, dst))
      {
        printf("R%d - R%d は接続しています。\n", src, dst);
      }
      else
      {
        printf("R%d - R%d は接続していません。\n", src, dst);
      }
    }

    putchar('\n');
  }
}
