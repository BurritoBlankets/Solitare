COMPILER=gcc
CFLAGS=-Wall -g

all: Solitare

Solitare: main.o logic.o graphics.o
	$(COMPILER) $(CFLAGS) logic.o graphics.o main.o -l ncurses

logic.o: logic.c
	$(COMPILER) $(CFLAGS) -c logic.c -l ncurses

graphics.o: graphics.c
	$(COMPILER) $(CFLAGS) -c graphics.c -l ncurses

main.o: main.c
	$(COMPILER) $(CFLAGS) -c main.c -l ncurses

clean:
	rm a.out *.o
