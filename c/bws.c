#include <stdio.h>
#include <string.h>

//#define DEBUG
#include "log.h"
#include "edgeInfo.h"

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
  gQueue.nodeInfoArray[gQueue.num] = *nodeInfo;
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

/* 再帰版 */
int isPassed_rec(struct nodeInfo *nodeInfo, int node)
{
  if(NULL == nodeInfo)
  {
    return 0;
  }

  if(nodeInfo->node == node)
  {
    return 1;
  }

  return isPassed_rec(nodeInfo->parent, node);
}

/* 非再帰版 */
int isPassed(struct nodeInfo *nodeInfo, int node)
{
  while(1)
  {
    if(!nodeInfo)
    {
      return 0;
    }

    if(nodeInfo->node == node)
    {
      return 1;
    }

    nodeInfo = nodeInfo->parent;
  }
}

void printRouteHelp(struct nodeInfo *nodeInfo)
{
  if(nodeInfo)
  {
    printf("%d ", nodeInfo->node);
    printRouteHelp(nodeInfo->parent);
  }
}

/* 再帰版 */
void printRoute_rec(struct nodeInfo *nodeInfo, int goal)
{
  printf("%d ", goal);
  printRouteHelp(nodeInfo);
  putchar('\n');
}

/* 非再帰版 */
void printRoute(struct nodeInfo *nodeInfo, int goal)
{
  printf("%d ", goal);
  while(nodeInfo)
  {
    printf("%d ", nodeInfo->node);
    nodeInfo = nodeInfo->parent;
  }
  putchar('\n');
}

/* 再帰版 */
void searchPath_rec(int goal)
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
      searchPath_rec(goal);
    }
  }
}

/* 非再帰版 */
void searchPath(int goal)
{
  while(1)
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
      }
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
  for(int i = 0; i < DEF_NODE_NUM; i++)
    for(int j = 0; j < DEF_NODE_NUM; j++)
    {
      runSearch(i, j);
      memset(&gQueue, 0x00, sizeof(gQueue));
    }

  return 0;
}
