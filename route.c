#include <stdio.h>

void printConnection(void);

/* 0 : 未接続, 1 : 接続 */
int pathInfo[7][7] ={
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
  return pathInfo[srcIndex][dstIndex];
}

struct routeInfo
{
  int startIndex;
  int goalIndex;
  int num;       /* 現在保持している件数 */
  int array[10]; /* 今までたどったルーター */
};

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

  printf("%d", ri.goalIndex);
}

void printCostInfo(struct routeInfo ri)
{
  printf("%d - %d : %d : ", ri.startIndex, ri.goalIndex, ri.num);
  printRoute(ri);
  putchar('\n');
}

/* 最初の目標 : 隣接しているルータ間のコストを算出できるようにする。*/
int printCostHelp(int currentIndex, struct routeInfo *routeInfo)
{
  //printf("DBG : %d : currentIndex = %d, goalIndex = %d\n", __LINE__, currentIndex, routeInfo->goalIndex);
  addRoute(routeInfo, currentIndex);

  /* 隣接ルータの接続判定 */
  if(isConnect(currentIndex, routeInfo->goalIndex))
  {
    printCostInfo(*routeInfo);
  }

  /* 自身が接続している別のルータを経由すればgoalIndexに到達できる可能性が残っている。*/
  int kouho;
  for(kouho = 0; kouho < 6; kouho++)
  {
    if(isConnect(currentIndex, kouho))
    {
      //printf("DBG : %d : currentIndex = %d, kouho = %d\n", __LINE__, currentIndex, kouho);

      /* 既に辿った経路の場合は除外する。*/
      if(passedRoute(*routeInfo, kouho))
      {
        continue;
      }

      /* 接続できる可能性が残っている。*/
      int cost2 = printCostHelp(kouho, routeInfo);
      if(cost2 == 0)
      {
        /* kouhoから接続できなかった場合 */
        popRoute(routeInfo);
        continue;
      }

      /* kouhoから接続できた場合 */
      //printf("DBG : %d : cost = %d, ", __LINE__, routeInfo->num);
      popRoute(routeInfo);
    }
  }

  /* 接続関係に無いルーターの場合 */
  return 0;
}

void printCost(int startIndex, int goalIndex)
{
  struct routeInfo routeInfo = { .startIndex = startIndex, .goalIndex = goalIndex, .num = 0 };
  printCostHelp(startIndex, &routeInfo);
}

int main(void)
{
  printCost(0, 6);
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


