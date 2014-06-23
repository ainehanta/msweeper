#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msweeper.h"

//コンテキストの作成
//w:ボードの幅
//h:ボードの高さ
MsContext* msInitContext(int w, int h)
{
  MsContext *context;
  char** tmp;
  int i;

  context = malloc(sizeof(MsContext));

  context->w = w;
  context->h = h;
  context->num = 0;

  tmp = malloc(sizeof(char*)*h);
  for(i=0;i<h;i++)
  {
    tmp[i] = malloc(sizeof(char)*w);
  }
  context->board = tmp;

  tmp = malloc(sizeof(char*)*h);
  for(i=0;i<h;i++)
  {
    tmp[i] = malloc(sizeof(char)*w);
  }
  context->disp_board = tmp;

  return context;
}

//コンテキストの廃棄
MsContext* msDestroyContext(MsContext* context)
{
  char** tmp;
  int i;

  tmp = context->board;
  for(i=0;i<context->h;i++)
  {
    free(tmp[i]);
  }
  free(tmp);

  tmp = context->disp_board;
  for(i=0;i<context->h;i++)
  {
    free(tmp[i]);
  }
  free(tmp);

  free(context);

  return NULL;
}

//ボードの作成
//最初の一手はボムが当たらないように、入力されてから
//ボードを作成する
//num:作成するボムの数
//x:最初に入力されたx座標
//y:最初に入力されたy座標
void msCreateBoard(MsContext *context,int num,int x,int y)
{
  char** tmp;
  int i;

  tmp = context->disp_board;
  for(i=0;i<context->h;i++)
  {
    memset(tmp[i],BOARD_CLOSE,sizeof(char)*context->w);
  }

  tmp = context->board;
  for(i=0;i<context->h;i++)
  {
    memset(tmp[i],BOARD_NONE,sizeof(char)*context->w);
  }

  msCreateBomb(context,num);
  msShuffleBoard(context);
  msExchangeValue(context,x,y);

  //D
  msPrintContext(context);
  msCalcBombNum(context);
}

//ボムの作成
//ボード配列にnum個ボムを代入
//num:ボム数
void msCreateBomb(MsContext *context,int num)
{
  int x,y;
  int tmp_num;
  char** tmp;

  context->num = num;

  tmp = context->board;
  tmp_num = num;
  for(y=0;y<=num/context->w;y++)
  {
    for(x=0;x<context->w&&tmp_num!=0;x++)
    {
      tmp_num--;
      tmp[y][x] = BOARD_BOMB;
    }
  }
}

//ボードをシャッフルする
void msShuffleBoard(MsContext *context)
{
  char** tmp;
  char swap;
  int x,y;
  int rx,ry;

  tmp = context->board;
  for(y=0;y<context->h;y++)
  {
    for(x=0;x<context->w;x++)
    {
      rx = rand()%context->w;
      ry = rand()%context->h;

      swap = tmp[ry][rx];
      tmp[ry][rx] = tmp[y][x];
      tmp[y][x] = swap;
    }
  }
}

//ボード上のランダムな位置と引数で指定された位置を入れ替える
//x:指定x座標
//y:指定y座標
void msExchangeValue(MsContext *context,int x,int y)
{
  char** tmp;
  int rx,ry;
  char swap;

  tmp = context->board;

  rx = rand()%context->w;
  ry = rand()%context->h;

  swap = tmp[ry][rx];
  tmp[ry][rx] = tmp[y][x];
  tmp[y][x] = swap;
}

//管理用ボード上各座標のボム数を計算して
//管理用ボードの各要素に代入
void msCalcBombNum(MsContext *context)
{
  char** board;
  int x,y;
  int bomb;

  board = context->board;
  for(y=0;y<context->h;y++)
  {
    for(x=0;x<context->w;x++)
    {
      bomb = 0;
      if(board[y][x] != BOARD_BOMB)
      {
        if(y-1>=0)
        {
          if(x-1>0) bomb += msIsBomb(context,x-1,y-1);
          bomb += msIsBomb(context,x,y-1);
          if(x+1<context->w) bomb += msIsBomb(context,x+1,y-1);
        }
        if(x-1>0) bomb += msIsBomb(context,x-1,y);
        bomb += msIsBomb(context,x,y);
        if(x+1<context->w) bomb += msIsBomb(context,x+1,y);
        if(y+1<context->h)
        {
          if(x-1>0) bomb += msIsBomb(context,x-1,y+1);
          bomb += msIsBomb(context,x,y+1);
          if(x+1<context->w) bomb += msIsBomb(context,x+1,y+1);
        }
        board[y][x] = bomb;
      }
    }
  }
}

//TODO
//指定座標のますを開く
//管理用ボードの値を見てボム以外なら表示用ボードにコピー
//ボムの場合は戻り値でゲームオーバー通知
//x,y:座標
int msOpenBoard(MsContext *context,int x,int y)
{
}

//TODO
//指定座標のマスにフラグを立てる
//x,y:座標
void msSetFlag(MsContext *context,int x,int y)
{
}

//管理用ボードの指定された座標がボムかどうか
//x,y:座標
//戻り値:1(ボム)
//       0(それ以外)
int msIsBomb(MsContext *context,int x,int y)
{
  if(context->board[y][x]==BOARD_BOMB)
    return 1;
  else
    return 0;
}

//TODO
//指定座標が操作可能な範囲か判定する
//戻り値: 1(可能)
//        0(不可能)
int msIsCorrectPosition(MsContext *context,int x,int y)
{
}

//TODO
//クリアしているか判定する
//クリアとは、すべてのボムにフラグが立っていること
//ゲームオーバーはmsOpenBoardで判断する
//戻り値: GAME_CLEAR(クリア)
//        GAME_SAFE(ゲーム中)
int msIsClear(MsContext *context)
{
}

//デバッグ用
//デバッグ用のなので非分割
void msPrintContext(MsContext *context)
{
  char** tmp;
  int x,y;

  printf("Debug Print : MsContext\n\n");

  printf("context->w   : %d\n",context->w);
  printf("context->h   : %d\n",context->h);
  printf("context->num : %d\n",context->num);

  tmp = context->board;
  printf("\nboard:\n");
  for(y=0;y<context->h;y++)
  {
    printf("%2d : ",y);
    for(x=0;x<context->w;x++)
    {
      if(tmp[y][x]==BOARD_BOMB)
      {
        printf("M");
      }
      else
      {
        printf("%d",tmp[y][x]);
      }
    }
    printf("\n");
  }

  tmp = context->disp_board;
  printf("\ndisp_board:\n");
  for(y=0;y<context->h;y++)
  {
    printf("%2d : ",y);
    for(x=0;x<context->w;x++)
    {
      if(tmp[y][x]==BOARD_BOMB)
      {
        printf("M");
      }
      if(tmp[y][x]==BOARD_FLAG)
      {
        printf("F");
      }
      else
      {
        printf("%d",tmp[y][x]);
      }
    }
    printf("\n");
  }
}
