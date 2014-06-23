#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "msweeper.h"
#include "ui.h"

#define BOMB 10

int main(void)
{
  MsContext *context;

  char buf[80];
  int x,y;
  int initialized = 0;

  //ランダム初期化
  //srand(1);
  srand((unsigned)time(NULL));

  while(1)
  {
    //コンテキスト作成
    context = msInitContext(8,8);

    do {
      //For Debug
      //msPrintContext(context);
      //uiPrintBoard(context,UI_BOARD);
      uiPrintBoard(context,UI_DISP_BOARD);
      printf("座標を入力してください(x y):");
      scanf("%d%d",&x,&y);

      if(msIsCorrectPosition(context,x,y)==0)
      {
        printf("入力範囲が適正ではありません\n");
        continue;
      }

      //入力されてから初期化し、最初からボムに当たらないように
      if(initialized==0)
      {
        msCreateBoard(context,BOMB,x,y);
        initialized++;
        buf[0] = 'o'; //強制的に開かせる
      }
      else
      {
        printf("開く・フラグをつける(o/f):");
        scanf("%s",buf);
      }


      if(buf[0]=='o')
      {
        if(msIsSetFlag(context,x,y)==1)
        {
          printf("フラグがすでにセットされています\n");
          continue;
        }

        if(msIsOpen(context,x,y)==1)
        {
          printf("すでに開かれています\n");
          continue;
        }
        if(msOpenBoard(context,x,y)==GAME_OVER)
        {
          //ボムだった場合、正解を表示して終わる
          uiPrintBoard(context,UI_BOARD);
          break;
        }
      }
      else if(buf[0]=='f')
      {
        if(msIsOpen(context,x,y)==1&&msIsSetFlag(context,x,y)==0)
        {
          printf("すでに開かれています\n");
          continue;
        }
        //フラグのトグル
        if(msIsSetFlag(context,x,y)==1)
          msUnSetFlag(context,x,y);
        else
          msSetFlag(context,x,y);
      }

    } while(msIsGameClear(context)==GAME_SAFE);

    if(msIsGameClear(context)==GAME_CLEAR)
    {
      printf("ゲームクリア\n");
    }
    else
    {
      printf("ゲームオーバー\n");
    }

    printf("リトライしますか?(y/n):");
    scanf("%s",buf);

    //コンテキスト開放
    context = msDestroyContext(context);
    initialized = 0;

    if(buf[0]=='n')
      break;
  }

  return 0;
}
