/******************************************************************************
 * File:    Solitare.c
 * Author:  Jose (Pillo) G. Duenas-Lopez
 * Version: 1.0 (May 10, 2023)
 *
 * Purpose:
 *          Toying around with ncurses with solitare
 *          gcc Solitare.c -o Solitare -l ncurses;  ./Solitare
 *          WHY ARE EMOJIS SO HARD!?!?!?!?!?
 *
 *****************************************************************************/

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>         /* to call srand            */
#include <time.h>           /* to seed srand            */
#include <ncurses.h>        /* graphical interface      */



int **shuffle_deck( void )
    /* creates and shuffles deck then returns value as a matrix */
{
    int of_a_kind = 0, redo = 0;
    int **deck;
    /* int deck[2][52]; first row determines card value, second row determines
     * card suite */


    deck = malloc( sizeof( int * ) * 2 );
    /* Allocates space for 2 rows */

    for( int i = 0; i < 2; i++ )
        /* For each row, allocate space for 52 columns */
    {
        deck[i] = malloc( sizeof( int ) * 52 );
    }


    for( int x = 0; x < 52; x++ )
        /* for each card in deck, assign a random card value */
    {
        do
        {
            of_a_kind = 5;
            /* condition checker for do-while) */

            deck[0][x] = rand() % 13 + 1;
            /*          1: ace         */
            /*         11: jack        */
            /*         12: queen       */
            /*         13: king        */
            /*  NUMBER TO CARD LEGEND  */

            for( int y = 0; y <= x; y++ )
                /* for each previous card, check that current card value hasn't been
                 * used more than 4 times */
            {
                if( deck[0][y] == deck[0][x] )
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


    for( int x = 0; x < 52; x++ )
        /* for each card in deck, assign a suite */
    {
        do
        {
            redo = 0;

            deck[1][x] = rand() % 4 + 1;
            /*        1: hearts       */
            /*        2: diamonds     */
            /*        3: clubs        */
            /*        4: spades       */
            /* NUMBER TO SUITE LEGEND */

            for( int y = 0; y < x; y++ )
                /* iterates over previous cards to check that current card value
                 * has not been over-used (more than 4 times) */
            {
                if( deck[0][y] == deck[0][x] && deck[1][y] == deck[1][x] )
                {
                    redo = 1;
                }
                else
                {
                    ; /* do nothing */
                }
            }
        }
        while( redo == 1 );
    }

    return deck;
}

void print_card( int y_axis, int x_axis, int value, int suite )
    /* prints cards with random value ?? still working the kinks */
{
    WINDOW * card = newwin( 6 , 8 , y_axis, x_axis );
    char suite_array[] = "HDCS";


    init_pair( 1, COLOR_WHITE, COLOR_BLACK);
    init_pair( 2, COLOR_BLACK, COLOR_WHITE );
    init_pair( 3, COLOR_RED, COLOR_WHITE );

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

void assign_tableau_values( int * deck )
{
    static int table_matrix[8][20];
    int x = 0;
    int row, col;

    for( int row = 1; row < 8; row++ )
        /*  prints tableau piles */
    {
        for( int col = 0; col < 8; col++ )
        {
            if( row - 1 > col )
            {
                table_matrix[row][col] = 32;
                printf( "%c", table_matrix[row][col]);
            }
            else if( row - 1 < col  )
            {
                table_matrix[row][col] = deck[x];
                printf( "%d ", table_matrix[row][col]);
                x++;
            }
        }
        printf( "\n" );
    }
}

void table_setup( int *row, int *col, int **deck )
{

    int z = 0;

    for( int x = 0; x < 7; x++ )
        /*  prints stock (1) and foundation (4) piles */
    {
        if( x != 1 && x != 2 )
        {
            print_card( row[0], col[x], 0, 0 );
        }
        else
        {
            ; /* do nothing */
        }
    }

    for( int x = 0; x <= 7; x++ )
        /*  prints tableau piles */
    {
        for( int y = 0; y <= 7; y++ )
        {
            if( x < y )
            {
                print_card( row[x+1], col[y-1], deck[0][z], deck[1][z] );
                z++;
            }
        }
    }
}

int main( void )
{
    srand( time( NULL ) );
    int **deck = shuffle_deck( );
    int *table_matrix[8][20];
    int table_col[7] = {3, 11, 19, 27, 35, 43, 51};
    int table_row[15] = {2, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34 };
    int game = true;
    int response;

    initscr();
    start_color();

    init_pair( 1, COLOR_WHITE, COLOR_GREEN);
    bkgd( COLOR_PAIR(1) );

    while( game == true )
    {
        table_setup( table_row, table_col, deck  );
        getchar();
        game = false;
    }

    getchar();
    endwin();


    //  /* prints deck matrix */
    //  for( int x = 0; x < 2; x++  )
    //  {
    //    for( int y = 0; y < 52; y++  )
    //    {
    //      printf("%d ", deck[x][y]);
    //    }
    //    printf("\n");
    //  }

    /* free space (deck matrix) */
    for( int i = 0; i < 2; i++ )
    {
        free( deck[i] );
    }
    free( deck );
    return 0;
