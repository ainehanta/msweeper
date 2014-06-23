/* curses ライブラリの使用例            */
/*                                      */
/* コンパイル方法					    */
/*   cc testcurses.c -lcurses	        */
/*							            */
/* 動作                                 */
/*   数字キーまたは矢印キーで示す方向に */
/*   @ が移動する                       */
/*   . で終了                           */
/*                                      */
/* 詳しい使い方は                       */
/*   man ncurses                        */

/* curses ライブラリを使う際に必要なヘッダ */
#include	<curses.h>

main(void)
{
  int num_count;
	int		x,y;
	int		c;
	int		oldc;

	/* 初期化と各種の設定 */
	initscr();
	//cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	addstr("*** testcurses ***");

  move(1,2);
  for(num_count=1;num_count<=4;num_count++)
  {
    addch(' ');
    addch(num_count + '0');
  }

	x = 25;
	y = 10;
	//move(y,x);
	//delch();
	//insch('@');
	refresh();
	while ((c = getch()) != '.'){
		//delch();
		//insch(oldc);
		switch(c){
		case '1':
			x--; y++; break;
		case '2':
			     y++; break;
		case '3':
			x++; y++; break;
		case '4':
			x--;      break;
		case '6':
			x++;      break;
		case '7':
			x--; y--; break;
		case '8':
			     y--; break;
		case '9':
			x++; y--; break;
		case KEY_LEFT:			/* 矢印キー */
			x--;      break;
		case KEY_RIGHT:
			x++;      break;
		case KEY_UP:
			     y--; break;
		case KEY_DOWN:
			     y++; break;
		}
		if (x < 0){
			//x = 0;
			x = 50;
		}else if (x > 50){
			//x = 50;
			x = 0;
		}
		if (y < 0){
			//y = 0;
			y = 20;
		}else if (y > 20){
			//y = 20;
			y = 0;
		}
		move(y,x);
		//oldc = inch();
		//delch();
		//insch('@');
		refresh();
	}
	endwin();
}
