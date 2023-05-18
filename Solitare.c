/******************************************************************************
 * File:    Solitare.c
 * Author:  Jose (Pillo) G. Duenas-Lopez
 * Version: 1.0 (May 10, 2023)
 *
 * Purpose:
 *          Toying around with ncurses with solitare
 *
 *****************************************************************************/

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>     /* to call srand */
#include <time.h>       /* to seed srand */
#include <ncurses.h>    /* visual aspect */

int * shuffle_deck( void );
/* shuffles deck then returns deck array */

void print_card( WINDOW * name, int y_cordinate, int x_cordinate );
/* prints cards */

int main( void )
{
    initscr();


    /* ROW 1 */
    WINDOW * stock;
    print_card( stock, 2, 3 );

    WINDOW * waste;
    print_card( waste, 2, 11 );

    WINDOW * foundation_1;
    print_card( foundation_1, 2, 27 );

    WINDOW * foundation_2;
    print_card( foundation_2, 2, 35 );

    WINDOW * foundation_3;
    print_card( foundation_3, 2, 43 );

    WINDOW * foundation_4;
    print_card( foundation_4, 2, 51 );


    /* ROW 2 (tableau) */
    WINDOW * tableau_1;
    print_card( tableau_1, 8, 3 );

    WINDOW * tableau_2;
    print_card( tableau_2, 8, 11 );

    WINDOW * tableau_3;
    print_card( tableau_3, 8, 19 );

    WINDOW * tableau_4;
    print_card( tableau_4, 8, 27 );

    WINDOW * tableau_5;
    print_card( tableau_5, 8, 35 );

    WINDOW * tableau_6;
    print_card( tableau_6, 8, 43 );

    WINDOW * tableau_7;
    print_card( tableau_7, 8, 51 );
    getchar();
    endwin();

    return 0;
}

void card_positions( void )
{
    /* ROW 1 */
    WINDOW * stock;
    print_card( stock, 2, 3 );

    WINDOW * waste;
    print_card( waste, 2, 11 );

    WINDOW * foundation_1;
    print_card( foundation_1, 2, 27 );

    WINDOW * foundation_2;
    print_card( foundation_2, 2, 35 );

    WINDOW * foundation_3;
    print_card( foundation_3, 2, 43 );

    WINDOW * foundation_4;
    print_card( foundation_4, 2, 51 );


    /* ROW 2 (tableau) */
    WINDOW * tableau_1;
    print_card( tableau_1, 8, 3 );

    WINDOW * tableau_2;
    print_card( tableau_2, 8, 11 );

    WINDOW * tableau_3;
    print_card( tableau_3, 8, 19 );

    WINDOW * tableau_4;
    print_card( tableau_4, 8, 27 );

    WINDOW * tableau_5;
    print_card( tableau_5, 8, 35 );

    WINDOW * tableau_6;
    print_card( tableau_6, 8, 43 );

    WINDOW * tableau_7;
    print_card( tableau_7, 8, 51 );
}

void print_card( WINDOW * name, int y_cordinate, int x_cordinate )
{

    name = newwin( 6 , 8 , y_cordinate , x_cordinate );
    box( name, '|', '-' );

    touchwin( name );
    wrefresh( name );
}

int * shuffle_deck( void )
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
