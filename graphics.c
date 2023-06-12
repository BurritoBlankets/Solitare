/******************************************************************************
 * File:    graphics.h
 *
 * Purpose:
 *          Ncurses functions which dictate how Solitaire is displayed in the
 *          CLI
 *
 * References:
 *          https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
 *          ^Man Pages^
 *
 *          https://gist.github.com/sylt/93d3f7b77e7f3a881603
 *          ^Mouse example^
 *
 * Notes:
 *          Work on mouse functions
 *
 *          Had to use standard ASCII characters to identify a cards suite
 *          because nurses doesn't support extended ASCII emoji 😔
 *
 *          Should I utilize the use of a matrix or of a function?
 *
 *****************************************************************************/



#include <curses.h>
#include <stdlib.h>         /* dynamic memory and random numbers            */
#include <ncurses.h>        /* graphical interface                          */
#include "functions.h"      /* solitaire functions                          */



void prerequisites( int y_max, int x_max )
    /* Checks for terminal size and color support */
{
    /* Checks terminal for color */
    if( has_colors() == false )
    {
        endwin();
        printf("ERROR: Terminal does not support color\n");
        exit(1);
    }
    else
    {
        start_color();
    }


    /* Checks terminal size */
    if(  y_max < 27 || x_max < 62 )
    {
        endwin();
        printf("ERROR: Terminal is too small (required: 62x27); Current size: %dx%d\n", x_max, y_max );
        exit(1);
    }
}


void print_card( int y_axis, int x_axis, int value, int suite )
    /* prints cards with random value ?? still working the kinks */
{
    WINDOW * card = newwin( 6 , 8 , y_axis, x_axis );
    char suite_array[] = "#$%&";
    /* char suite_array[] = "♥️♦️♣️♠️"; // ncurses != emoji support */


    init_pair( 1, COLOR_WHITE, COLOR_GREEN);
    init_pair( 2, COLOR_BLACK, COLOR_WHITE );
    init_pair( 3, COLOR_RED, COLOR_WHITE );
    init_pair( 4, COLOR_GREEN, COLOR_GREEN );

    wbkgd( card, COLOR_PAIR(2) );     /* card filler*/
    wattrset( card, COLOR_PAIR(1) );  /* card outline  */
    box( card, 0, 0 );

    if( suite < 3 )
        /* if card is a heart or diamond, then card print color is red */
    {
        wattrset( card, COLOR_PAIR( 3 ) );
    }
    else if( suite > 2 )
        /* if card is a clubs or spades, then card print color is black */
    {
        wattrset( card, COLOR_PAIR( 2 ) );
    }

    if( value == 0 )
        /* determines card value to set printing location and what is printed */
    {
        ; /* do nothing */
    }
    else if( value == 1 )
    {
        mvwprintw( card, 1, 5, "A");
    }
    else if( value < 10 )
    {
        mvwprintw( card, 1, 5, "%d", value);
    }
    else if( value == 10 )
    {
        mvwprintw( card, 1, 4, "%d", value);
    }
    else if( value == 11 )
    {
        mvwprintw( card, 1, 5, "J");
    }
    else if( value == 12 )
    {
        mvwprintw( card, 1, 5, "Q");
    }
    else if( value == 13 )
    {
        mvwprintw( card, 1, 5, "K");
    }


    if( suite > 0 && suite < 5 )
        /* determines card suite to set what is printed */
    {
        wprintw(card, "%c",suite_array[suite - 1]) ;
    }
    else
    {
        ; /* do nothing */
    }


    touchwin( card );
    wrefresh( card );
}


void print_background( int y_max, int x_max )
{
    WINDOW * background = newwin( y_max, x_max, 0, 0 );

    init_pair( 1, COLOR_GREEN, COLOR_BLACK );

    wbkgd( background, COLOR_PAIR(1) );
    wattrset( background, COLOR_PAIR(1) );  /* card outline  */
    box( background, 0, 0 );

    touchwin( background );
    wrefresh( background );

}


void set_table( int *row, int *col, int **deck )
{
    int z = 0;

    for( int x = 0; x < 7; x++ )
        /*  prints stock (1) and foundation (4) piles */
    {
        if( x != 1 && x != 2 )
        {
            print_card( row[0], col[x], 0, 0 );
        }
    }

    for( int x = 0; x <= 7; x++ )
        /*  prints tableau piles */
    {
        for( int y = 0; y <= 7; y++ )
        {
            if( x < y )
            {
                print_card( row[x+1], col[y-1], deck[z][0], deck[z][1] );
                z++;
            }
        }
    }
}


