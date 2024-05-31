#include "edgeInfo.h"

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
