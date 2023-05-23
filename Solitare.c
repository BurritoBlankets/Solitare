/******************************************************************************
 * File:    Solitare.c
 * Author:  Jose (Pillo) G. Duenas-Lopez
 * Version: 1.0 (May 10, 2023)
 *
 * Purpose:
 *          Toying around with ncurses with solitare
 *          gcc Solitare.c -o Solitare -l ncurses;  ./Solitare
 *
 *****************************************************************************/

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>     /* to call srand */
#include <time.h>       /* to seed srand */
#include <ncurses.h>    /* visual aspect */

int * shuffle_deck( void );
/* shuffles deck then returns deck array */

void print_card( int y_axis, int x_axis, int value );
/* prints cards with random value ?? still working the kinks */

int main( void )
{
    initscr();

    int card_column[7] = {3, 11, 19, 27, 35, 43, 51};
    int card_row[15] = {2, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34 };
    int * deck = shuffle_deck( );

    for( int x = 0; x < 7; x++ )
    /*  prints stock (1) and foundation (4) piles */
    {
        if( x != 1 && x != 2 )
        {
            print_card( card_row[0], card_column[x], 0 );
        }
        else
        {
            ; /* do nothing */
        }
    }

    for( int x = 1; x < 8; x++ )
    /*  prints tableau piles */
    {
        for( int y = 0; y < 8; y++ )
        {
            if( x-1 > y )
            {
                ; /* do nothing */
            }
            else
            {
                print_card( card_row[x], card_column[y], 0 );
            }
        }
    }
    getchar();
    endwin();
}

int * shuffle_deck( void )
/* shuffles deck then returns deck array */
{
    static int deck[51];
    int of_a_kind;

        for( int x=0; x <= 51; x++ )
    /* for each card in deck, assign a random card value */
    {
        do
        {
            of_a_kind = 5;
            /* ^used to ensure that there is exactly 4 of a kind. (condition
             * checker for do-while loop) */

            deck[x] = rand() % 13 + 1;

            for( int y=0; y <= x; y++ )
            /* iterates over previous cards to check that current card value
             * has not been over-used (more than 4 times) */
            {
                if( deck[y] == deck[x] )
                {
                    of_a_kind--;
                }
                else
                {
                    ; /* do nothing */
                }
            }
        }
        while( of_a_kind == 0 );
    }
    return deck;
}

void print_card( int y_axis, int x_axis, int value )
{
    WINDOW * card = newwin( 6 , 8 , y_axis, x_axis );
    box( card, 0, 0 );


    if( value == 0 )
    {
        ; /* do nothing */
    }
    else if( value <= 9 )
    {
        mvwprintw( card, 1, 6, "%d", value);
    }
    else if( value == 10 )
    {
        mvwprintw( card, 1, 5, "%d", value);
    }
    else if( value == 11 )
    {
        mvwprintw( card, 1, 6, "J");
    }
    else if( value == 12 )
    {
        mvwprintw( card, 1, 6, "Q");
    }
    else if( value == 13 )
    {
        mvwprintw( card, 1, 6, "K");
    }

    touchwin( card );
    wrefresh( card );

}
