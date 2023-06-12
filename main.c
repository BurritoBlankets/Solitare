/******************************************************************************
 * File:    main.c
 * Author:  Pillo Duenas-Lopez
 * Version: 0.0 (JUN, 01, 2023)
 *
 * Purpose:
 *          Terminal playable solitaire
 *
 *****************************************************************************/



#include <stdio.h>
#include <stdlib.h>         /* dynamic memory  &  random numbers            */
#include <time.h>           /* seeds srand()                                */
#include <ncurses.h>        /* graphical interface                          */
#include "functions.h"      /* graphics.c functions                         */



int main( void )
{
    srand( time( NULL ) );
    int **deck = shuffle_deck( );
    int table_col[7] = {3, 11, 19, 27, 35, 43, 51};
    int table_row[15] = {1, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34 };
    int horizontal_max, vertical_max, ch;
    MEVENT event;


    initscr();
    getmaxyx(stdscr, horizontal_max, vertical_max);
    prerequisites( horizontal_max ,vertical_max );


    mousemask( BUTTON1_PRESSED | REPORT_MOUSE_POSITION, NULL );
    keypad( stdscr, TRUE ); /* enables use of arrows */
    cbreak( ); /* disables need for carriage return */
    noecho( ); /* disables auto-echoing */


    while( true )
    {
        print_background( horizontal_max, vertical_max );
        set_table( table_row, table_col, deck );
        ch = wgetch( stdscr );
        if( ch == KEY_MOUSE )
        {
            if( getmouse( &event ) == OK )
            {
                mvwprintw(stdscr, 0, 0, "row: %d ; col: %d ", event.y, event.x );

            }
        }
    }

    endwin();
    free_matrix( deck );
    return 0;
}
