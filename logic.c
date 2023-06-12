/******************************************************************************
 * File:    Solitare.c
 * Author:  Pillo Duenas-Lopez
 *
 * Purpose:
 *          A bunch of functions that manipulate the deck as the game
 *          progresses
 *
 * Notes:
 *          WHY ARE EMOJIS SO HARD!?!?!?!?!?
 *
 *****************************************************************************/



#include <stdio.h>
#include <stdlib.h>         /* dynamic memory and random numbers            */
#include "functions.h"      /* solitaire functions                          */



/******************************************************************************
void assign_tableau_values( int * deck )
{
    static int table_matrix[8][20];
    int x = 0;
    int row = 0, col = 0;

    for( int row = 1; row < 8; row++ )
        //  prints tableau piles //
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

******************************************************************************/


void free_matrix( int **matrix )
/* free all dynamic memory */
{
    /* free space (deck matrix) */
    for( int i = 0; i < 2; i++ )
    {
        free( matrix[i] );
    }
    free( matrix );
}


int **make_matrix( int x, int y )
{
    int **matrix;

    matrix = malloc( sizeof( int * ) * x );
    /* Allocates space for 'x' columns */

    for( int i = 0; i < x; i++ )
        /* For each row, allocate space for 'y' rows */
    {
        matrix[i] = malloc( sizeof( int ) * y );
    }

    return matrix;
}


int **shuffle_deck( void )
    /* shuffles deck then returns value as a matrix */
{
    int of_a_kind = 0, redo = 0;
    int **deck = make_matrix(52, 2);
    /* int deck[2][52]; first row determines card value, second row determines
     * card suite */

    for( int x = 0; x < 52; x++ )
        /* for each card in deck, assign a random card value */
    {
        do
        {
            of_a_kind = 5;
            /* condition checker for do-while) */
            deck[x][0] = rand() % 13 + 1;
            /*         1: ace         */
            /*        11: jack        */
            /*        12: queen       */
            /*        13: king        */
            /*  NUMBER TO CARD LEGEND */

            for( int prev = 0; prev <= x; prev++ )
                /* for each previous card, check that current card value hasn't been
                 * used more than 4 times */
            {
                if( deck[prev][0] == deck[x][0] )
                {
                    of_a_kind--;
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

            deck[x][1] = rand() % 4 + 1;
            /*        1: hearts       */
            /*        2: diamonds     */
            /*        3: clubs        */
            /*        4: spades       */
            /* NUMBER TO SUITE LEGEND */

            for( int y = 0; y < x; y++ )
                /* iterates over previous cards to check that current card value
                 * has not been over-used (more than 4 times) */
            {
                if( deck[y][0] == deck[x][0] && deck[y][1] == deck[x][1] )
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


