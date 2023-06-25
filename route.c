#include <stdio.h>

void printConnection(void);

/* 0 : 未接続, 1 : 接続 */
int pathInfo[6][6] ={
  {0, 1, 1, 0, 0, 1}, /* R0-RX間の接続 */
  {1, 0, 1, 0, 0, 0},
  {1, 1, 0, 1, 0, 0},
  {0, 0, 1, 0, 1, 0},
  {0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 1}
};

/* 接続関係にあれば、1を、なければ、0を返す。*/
int isConnect(int srcIndex, int dstIndex)
{
  return pathInfo[srcIndex][dstIndex];
}

struct routeInfo
{
  int num;       /* 現在保持している件数 */
  int array[10]; /* 今までたどったルーター */
};

#if 0
void addRoute(struct routeInfo *ri, int newRout)
{
  int num = ri->num;
  ri->array[num] = newRout;

  num++;
  ri->num = num;
}
#endif

void addRoute(struct routeInfo *ri, int newRout)
{
  int *pNum = &ri->num;
  ri->array[*pNum] = newRout;

  (*pNum)++;
}

void popRoute(struct routeInfo *ri)
{
  if(0 >= ri->num)
  {
    return;
  }

  ri->num--;
}

int passedRoute(struct routeInfo ri, int route)
{
  int i;
  for(i = 0; i < ri.num; i++)
  {
    if(ri.array[i] == route)
    {
      return 1;
    }
  }

  return 0;
}

void printRoute(struct routeInfo ri)
{
  for(int i = 0; i < ri.num; i++)
  {
    printf("%d ", ri.array[i]);
  }
}

/* 最初の目標 : 隣接しているルータ間のコストを算出できるようにする。*/
int calcCost(int startIndex, int goalIndex, struct routeInfo *routeInfo)
{
  printf("DBG : %d : startIndex = %d, goalIndex = %d\n", __LINE__, startIndex, goalIndex);
  addRoute(routeInfo, startIndex);

  /* 隣接ルータの接続判定 */
  if(isConnect(startIndex, goalIndex))
  {
    printf("cost = %d, ", routeInfo->num);
    addRoute(routeInfo, goalIndex);
    printRoute(*routeInfo);
    putchar('\n');
    popRoute(routeInfo);

    return routeInfo->num;
  }

  /* 自身が接続している別のルータを経由すればgoalIndexに到達できる可能性が残っている。*/
  int kouho;
  for(kouho = 0; kouho < 6; kouho++)
  {
    if(isConnect(startIndex, kouho))
    {
      printf("DBG : %d : startIndex = %d, kouho = %d\n", __LINE__, startIndex, kouho);

      /* 既に辿った経路の場合は除外する。*/
      if(passedRoute(*routeInfo, kouho))
      {
        continue;
      }

      /* 接続できる可能性が残っている。*/
      int cost2 = calcCost(kouho, goalIndex, routeInfo);
      if(cost2 == -1)
      {
        /* kouhoから接続できなかった場合 */
        popRoute(routeInfo);
        continue;
      }

      /* kouhoから接続できた場合 */
      printf("DBG : %d : cost = %d, ", __LINE__, routeInfo->num);
      popRoute(routeInfo);
    }
  }

  /* 接続関係に無いルーターの場合 */
  return -1;
}


int main(void)
{
#if 0
  int goal;
  for(goal = 0; goal < 6; goal++)
  {
    int cost = calcCost(0, goal);
    printf("R0 - R%d 間のコストは%2dです。\n", goal, cost);
  }
#endif

  struct routeInfo routeInfo = { .num = 0 };

  int cost = calcCost(0, 3, &routeInfo);
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


