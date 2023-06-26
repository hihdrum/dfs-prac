#include <stdio.h>

#define DEF_ROUTER_NUM (7)

void printConnection(void);

/* 0 : 未接続, 1 : 接続 */
int pathInfo[DEF_ROUTER_NUM][DEF_ROUTER_NUM] ={
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

void pushRoute(struct routeInfo *ri, int newRout)
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

int printCostHelp(struct routeInfo *routeInfo)
{
  //printf("DBG : %d : currentIndex = %d, goalIndex = %d\n", __LINE__, currentIndex, routeInfo->goalIndex);

  /* 現在のルーターと接続関係にあるルーターを網羅的に調べる。*/
  int kouho;
  for(kouho = 0; kouho < DEF_ROUTER_NUM; kouho++)
  {
    if(isConnect(routeInfo->array[routeInfo->num - 1], kouho))
    {
      //printf("DBG : %d : currentIndex = %d, kouho = %d\n", __LINE__, currentIndex, kouho);

      /* 候補がゴールだった場合は結果を出力する。*/
      if(kouho == routeInfo->goalIndex)
      {
        printCostInfo(*routeInfo);
        continue;
      }

      /* 既に辿った経路の場合は除外する。*/
      if(passedRoute(*routeInfo, kouho))
      {
        continue;
      }

      /* 別のルーターを経由して到達できるかを調べる。*/
      pushRoute(routeInfo, kouho);
      printCostHelp(routeInfo);
      popRoute(routeInfo);
    }
  }

  /* 接続関係に無いルーターの場合 */
  return 0;
}

void printCost(int startIndex, int goalIndex)
{
  struct routeInfo routeInfo = { .startIndex = startIndex, .goalIndex = goalIndex, .num = 0 };
  pushRoute(&routeInfo, startIndex);
  printCostHelp(&routeInfo);
  popRoute(&routeInfo);
}

int main(void)
{
  printCost(0, 5);
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


