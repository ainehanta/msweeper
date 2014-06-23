#ifndef __UI_H_
#define __UI_H_

#include "msweeper.h"

#define UI_BOARD  0
#define UI_DISP_BOARD 1

#define UI_CLOSE  '.'
#define UI_OPEN   ' '
#define UI_FLAG   'F'
#define UI_BOMB   'M'

//ボードの内容を表示する
//引数でどちらのボードを表示するか選択可能
//select:UI_BOARD(context->board)
//       UI_DISP_BOARD(context->disp_board)
void uiPrintBoard(MsContext *context,int select);

//ボードの上の数字を表示
void uiPrintColNum(MsContext *context);

//ボード配列内の値を文字に変換して出力
void uiPrintChar(char ch);
#endif
