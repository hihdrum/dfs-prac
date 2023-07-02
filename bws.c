#include <stdio.h>
#include <string.h>

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

/* 幅優先探索向け */
/*-----------------------------------------------*/
struct nodeInfo
{
  int node;
  struct nodeInfo *parent;
};

struct queue
{
  int num;
  int point;
  struct nodeInfo nodeInfoArray[DEF_NODE_NUM * DEF_NODE_NUM];
};

struct queue gQueue;

void printQueue(void)
{
  printf("gQueue, num = %d, point = %d\n", gQueue.num, gQueue.point);
  for(int i = 0; i < gQueue.num; i++)
  {
    struct nodeInfo *nodeInfo = &gQueue.nodeInfoArray[i];
    printf("%d, %p, node = %d, parent = %p\n", i, nodeInfo, nodeInfo->node, nodeInfo->parent);
  }
}

void inqueue(struct nodeInfo *nodeInfo)
{
  LOG("nodeInfo = %p, node = %d, parent = %p\n", nodeInfo, nodeInfo->node, nodeInfo->parent);
  memcpy(&gQueue.nodeInfoArray[gQueue.num], nodeInfo, sizeof(struct nodeInfo));
  gQueue.num++;

  //printQueue();
}

struct nodeInfo *dequeue(void)
{
  if(gQueue.point >= gQueue.num)
  {
    return NULL;
  }

  struct nodeInfo *ret = &gQueue.nodeInfoArray[gQueue.point];

  gQueue.point++;
  LOG("num = %d, point = %d\n", gQueue.num, gQueue.point);
  return ret;
}

int isPassed(struct nodeInfo *nodeInfo, int node)
{
  if(NULL == nodeInfo)
  {
    return 0;
  }

  if(nodeInfo->node == node)
  {
    return 1;
  }

  return isPassed(nodeInfo->parent, node);
}

void printRouteHelp(struct nodeInfo *nodeInfo)
{
  if(nodeInfo)
  {
    printf("%d ", nodeInfo->node);
    printRouteHelp(nodeInfo->parent);
  }
}

void printRoute(struct nodeInfo *nodeInfo, int goal)
{
  printf("%d ", goal);
  printRouteHelp(nodeInfo);
  putchar('\n');
}

void searchPath(int goal)
{
  struct nodeInfo *currentNodeInfo = dequeue();
  if(NULL == currentNodeInfo) { return; }

  for(int nextNode = 0; nextNode < DEF_NODE_NUM; nextNode++)
  {
    if(isConnect(currentNodeInfo->node, nextNode))
    {
      if(nextNode == goal)
      {
        printRoute(currentNodeInfo, goal);
        continue;
      }

      if(isPassed(currentNodeInfo, nextNode))
      {
        continue;
      }

      /* 到達可能性のあるノードを候補として追加する。*/
      inqueue(&(struct nodeInfo){ .node = nextNode, .parent = currentNodeInfo});
      searchPath(goal);
    }
  }
}

void runSearch(int start, int goal)
{
  LOG("start = %d, goal = %d\n", start, goal);
  if(start == goal)
  {
    return;
  }

  inqueue(&(struct nodeInfo){ .node = start, .parent = NULL });
  searchPath(goal);
}

int main(void)
{
  runSearch(0, 3);
  return 0;
}
