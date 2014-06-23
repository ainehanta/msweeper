#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "msweeper.h"

int main(void)
{
  MsContext *context;
  srand(1);

  context = msInitContext(8,8);

  msPrintContext(context);
  msCreateBoard(context,10,1,1);
  msPrintContext(context);
  
  printf("GAME_STATUS:%d\n",msOpenBoard(context,0,0));
  msPrintContext(context);

  printf("GAME_STATUS:%d\n",msOpenBoard(context,6,0));
  msPrintContext(context);

  context = msDestroyContext(context);

  return 0;
}
