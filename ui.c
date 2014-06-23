#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "ui.h"
#include "msweeper.h"

//ボードの内容を表示する
//引数でどちらのボードを表示するか選択可能
//select:UI_BOARD(context->board)
//       UI_DISP_BOARD(context->disp_board)
void uiPrintBoard(MsContext *context,int select)
{
  char** board;
  int x,y;

  //表示するボード切り替え
  switch(select)
  {
    case UI_BOARD :
      board = context->board;
      break;
    case UI_DISP_BOARD :
      board = context->disp_board;
      break;
    default:
      return;
  }

  for(y=0;y<context->h;y++)
  {
    if(y==0)
      uiPrintColNum(context);

    for(x=0;x<context->w;x++)
    {
      if(x==0)
        printf("%2d",y);
      uiPrintChar(board[y][x]);
    }
    printf("\n");
  }


}

//ボードの上の数字を表示
void uiPrintColNum(MsContext *context)
{
  int i;
  printf("  ");
  for(i=0;i<context->w;i++)
  {
    printf("%2d",i);
  }
  printf("\n");
}

//ボード配列内の値を文字に変換して出力
void uiPrintChar(char ch)
{
  //変換テーブル
  switch(ch)
  {
    case BOARD_BOMB :
      ch = UI_BOMB;
      break;
    case BOARD_CLOSE :
      ch = UI_CLOSE;
      break;
    case BOARD_OPEN :
      ch = UI_OPEN;
      break;
    case BOARD_FLAG :
      ch = UI_FLAG;
      break;
    default:
      ch += '0';
      break;
  }

  printf("%2c",ch);
}
