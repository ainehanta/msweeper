#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "msweeper.h"

int main(void)
{
  MsContext *context;
  srand((unsigned)time(NULL));

  context = msInitContext(8,8);

  msPrintContext(context);
  msCreateBoard(context,10,1,1);
  msPrintContext(context);

  context = msDestroyContext(context);

  return 0;
}
