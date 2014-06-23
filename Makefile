TARGET = msweeper
SRCS = main.c msweeper.c ui.c

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -lncurses 

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.c.o :
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJS) $(TARGET)

msweeper.c : msweeper.h
ui.c : ui.h
main.c : msweeper.c ui.c
