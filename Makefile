CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c2x -O2
vpath %.c src

NAME = engbench

UNAME_S := $(shell uname -s)
EXE = $(NAME)
ifneq (,$(findstring MINGW, $(UNAME_S)))
EXE = $(NAME).exe
endif

SRCS = main.c
OBJS = $(SRCS:%.c=%.o)

LIBS = -lncurses -lpanel -lmenu -lform -lm

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) $(EXE)
