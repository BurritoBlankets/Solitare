#pragma once


/* Libraries                                                                */
#include <stdio.h>
#include <stdlib.h>         /* dynamic memory and random numbers            */
#include <string.h>
#include <math.h>
#include <time.h>           /* seeds srand()                                */
#include <ncurses.h>        /* graphical interface                          */
#include <curses.h>
#include <panel.h>
#include <locale.h>



typedef struct node
{
  int value;
  int suite;
  struct node *next;
}
pile;


/* Re-Print Screen */
void print_background( void );
void print_foundations( int **coordinates );
void print_stock( int **coordinates, int **deck, int value, int suite);
void print_tableau(int ***tableau );
void print_card( WINDOW *card, int value, int suite, int atributes, int stock_pile );

/* Allocate Dynamic Memory */
int ***multi_dimensional( int x, int y, int z );
int **matrix( int x, int y );

/* Free Dynamic Memory */
void free_dimensions( int ***matrix, int x, int y );
void free_matrix( int **matrix, int x );

/* Refresh */
int **card_placement( int col, int row ); //THIS A NEW ONE
int **placement_refresh( void );

/* Initiation */
int ***set_tableau( int **coordinates, int **deck);
int **shuffle_deck( void );
pile *set_stock( int **deck, pile *head );
void prerequisites( void );

/* Buttons */
void tableau_click( int ***tableau, MEVENT event );


