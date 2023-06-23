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

/* 最初の目標 : 隣接しているルータ間のコストを算出できるようにする。*/
int calcCost(int startIndex, int goalIndex)
{
  int cost = 0;

  /* 接続判定 */
  if(isConnect(startIndex, goalIndex))
  {
    cost++;
  }
  else
  {
    cost = -1;
  }

  return cost;
}

int main(void)
{
  int goal;
  for(goal = 0; goal < 6; goal++)
  {
    int cost = calcCost(0, goal);
    printf("R0 - R%d 間のコストは%2dです。\n", goal, cost);
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


