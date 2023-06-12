#pragma once


/* Libraries                                                                */
#include <stdio.h>
#include <stdlib.h>         /* dynamic memory and random numbers            */
#include <ncurses.h>        /* graphical interface                          */



/* graphics.c                                                               *
 * Ncurses functions which dictate how Solitaire is displayed in the CLI    */
void prerequisites( int y_max, int x_max );
void print_background( int y_max, int x_max );
void print_card( int y_axis, int x_axis, int value, int suite );
void set_table( int *row, int *col, int **deck );


/* logic.c                                                                  *
 * A bunch of functions that manipulate the deck as the game progresses     */
void assign_tableau_values( int * deck );
void free_matrix( int **deck );
void get_center_array( int y_max, int x_max );
int **make_matrix( int x, int y );
int **shuffle_deck( void );


