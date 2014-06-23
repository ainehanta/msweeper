#define __DEBUG

#ifndef __DEBUG_H
#define __DEBUG_H

//デバッグ用マクロ
//__DP デバッグ出力
//__DEXE デバッグ実行
//__DEBUGが定義されているか否かでソースを切り替える

#ifdef __DEBUG
#define __DP printf
#define __DEXE
#else
#define __DP 1 ? (void) 0 : printf
#define __DEXE 1 ? (void) 0 :
#endif

#endif
