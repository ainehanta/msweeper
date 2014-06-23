#ifndef __MSWEEPER_H
#define __MSWEEPER_H

#define BOARD_BOMB   -1
#define BOARD_NONE   0

#define BOARD_CLOSE  0
#define BOARD_1      1
#define BOARD_2      2
#define BOARD_3      3
#define BOARD_4      4
#define BOARD_5      5
#define BOARD_6      6
#define BOARD_7      7
#define BOARD_8      8

#define BOARD_FLAG   9

//コンテキスト
//disp_board:表示用ボード
//board:管理用ボード
//h:ボード幅
//w:ボード高さ
//num:ボム数
struct _MsContext
{
  char** disp_board;
  char** board;
  int h;
  int w;
  int num;
};

typedef struct _MsContext MsContext;

//コンテキストの作成
//w:ボードの幅
//h:ボードの高さ
MsContext* msInitContext(int w, int h);

//コンテキストの廃棄
MsContext* msDestroyContext(MsContext* context);

//ボードの作成
//最初の一手はボムが当たらないように、入力されてから
//ボードを作成する
//num:作成するボムの数
//x:最初に入力されたx座標
//y:最初に入力されたy座標
void msCreateBoard(MsContext *context,int num,int x,int y);

//ボムの作成
//ボード配列にnum個ボムを代入
//num:ボム数
void msCreateBomb(MsContext *context,int num);

//ボードをシャッフルする
void msShuffleBoard(MsContext *context);

//ボード上のランダムな位置と引数で指定された位置を入れ替える
//x:指定x座標
//y:指定y座標
void msExchangeValue(MsContext *context,int x,int y);

//管理用ボード上各座標のボム数を計算して
//管理用ボードの各要素に代入
void msCalcBombNum(MsContext *context);

//TODO
//指定座標のますを開く
//管理用ボードの値を見てボム以外なら表示用ボードにコピー
//ボムの場合は戻り値でゲームオーバー通知
//x,y:座標
int msOpenBoard(MsContext *context,int x,int y);

//TODO
//指定座標のマスにフラグを立てる
//x,y:座標
void msSetFlag(MsContext *context,int x,int y);

//管理用ボードの指定された座標がボムかどうか
//x,y:座標
//戻り値:1(ボム)
//       0(それ以外)
int msIsBomb(MsContext *context,int x,int y);

//TODO
//指定座標が操作可能な範囲か判定する
//戻り値: 1(可能)
//        0(不可能)
int msIsCorrectPosition(MsContext *context,int x,int y);

//TODO
//クリアしているか判定する
//クリアとは、すべてのボムにフラグが立っていること
//ゲームオーバーはmsOpenBoardで判断する
//戻り値: GAME_CLEAR(クリア)
//        GAME_SAFE(ゲーム中)
int msIsClear(MsContext *context);

//デバッグ用
//コンテキスト内容を表示
void msPrintContext(MsContext *context);

#endif
