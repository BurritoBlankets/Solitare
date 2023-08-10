COMPILER=gcc
CFLAGS=-Wall -g

all: Solitare

Solitare: main.o logic.o graphics.o
	$(COMPILER) $(CFLAGS) logic.o graphics.o main.o -lncurses -lpanel

logic.o: logic.c
	$(COMPILER) $(CFLAGS) -c logic.c -lncurses -lpanel

graphics.o: graphics.c
	$(COMPILER) $(CFLAGS) -c graphics.c -lncurses -lpanel

main.o: main.c
	$(COMPILER) $(CFLAGS) -c main.c -lncurses -lpanel

clean:
	rm a.out *.o
