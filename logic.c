/****************************************************************************
 * File:    logic.c
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

#include "functions.h"      /* solitaire functions                          */


void tableau_click( int ***tableau, MEVENT event )
{
  /* Get Clickable Coordinates: */
  for( int row = 0; row < 7; row++ ) /* for every row in table*/
  {
    for( int col = 0; col < 15; col++ )  /* for every col in table*/
    {
      if(   tableau[row][col][2] == 1             /* if show card */
          &&  event.y >= tableau[row][col][3]-col     /* Top R */
          &&  event.y <= tableau[row][col][3]+6       /* Top L */
          &&  event.x >= tableau[row][col][4]+1       /* Bot R */
          &&  event.x <= tableau[row][col][4]+8       /* Bot L */
        )
      {
        tableau[row][col][2] = 2;   /* mark card as clicked  */
      }
    }
  }
}

void print_card( WINDOW *card, int value, int suite, int atributes, int stock_pile )
{
  char suite_array[] = "#$%&";

  if( atributes == 2 )
  /* if card is clicked, enable yellow highlight */
  {
    box( card, 0, 0 );
    wbkgd( card, COLOR_PAIR(7) );
  }
  else
  /* otherwise, background is white */
  {
    wbkgd( card, COLOR_PAIR(2) );
  }


  if( suite < 3 )
  /* if card suite is a heart or diamond, then card print color is red */
  {
    wattrset( card, COLOR_PAIR( 3 ) );
  }
  else if( suite > 2 )
  /* if card is a clubs or spades, then card print color is black */
  {
    wattrset( card, COLOR_PAIR( 2 ) );
  }


  if( value == 1 )
  {
    mvwprintw( card, stock_pile, stock_pile, "A");
  }
  else if( value < 11 )
  {
    mvwprintw( card, stock_pile, stock_pile, "%d", value );
  }
  else if( value == 11 )
  {
    mvwprintw( card, stock_pile, stock_pile, "J");
  }
  else if( value == 12 )
  {
    mvwprintw( card, stock_pile, stock_pile, "Q");
  }
  else if( value == 13 )
  {
    mvwprintw( card, stock_pile, stock_pile, "K");
  }

  /* print suite */
  wprintw(card, "%c",suite_array[suite - 1]) ;

}

int ***multi_dimensional( int x, int y, int z )
{
  int ***tree_d = NULL;

    tree_d = malloc( sizeof( int** ) * x );
    for( int i = 0; i < x; i++ )
    {
        tree_d[i] = malloc( sizeof( int* ) * y );
      for( int j = 0; j < y; j++ )
      {
        tree_d[i][j] = malloc( sizeof( int ) * z );
      }
    }


    /* set each element to 0 */
  for( int i = 0; i < x; i++ )
    for( int j = 0; j < y; j++ )
      for( int k = 0; k < z; k++ )
        tree_d[i][j][k] = 0;

  return tree_d;
}


int **matrix( int x, int y )
{
  int **matrix;

  matrix = malloc( sizeof( int * ) * x );

  for( int i = 0; i < x; i++ )
  {
    matrix[i] = malloc( sizeof( int ) * y );
  }


  for( int i = 0; i < x; i++ )
    /* set each element to 0 */
  {
    for( int j = 0; j < y; j++ )
    {
      matrix[i][j] = 0;
    }
  }

  return matrix;
}


void free_dimensions( int ***tree_d, int x, int y )
/* deallocate memory */
{
    for( int i = 0; i < x; i++ )
    {
        for( int j = 0; j < y; j++ )
        {
            free(tree_d[x][y]);
        }
        free(tree_d[x]);
    }
    free(tree_d);
}


void free_matrix( int **matrix, int x )
/* deallocate memory */
{
    for( int i = 0; i < x; i++ )
    {
        free(matrix[i]);
    }
    free(matrix);
}


int **placement_refresh( void )
{
  /****************************************************************************
   * Looks for a change in screen size, then manipulates the table matrix
   * accordingly to ensure everything is centered.
   *
   *TABLE MATRIX (BEFORE MANIPULATION):
   *table[i][0] (col: 1,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34)
   *table[i][1] (row: 3, 11, 19, 27, 35, 43, 51,  0,  0,  0,  0,  0,  0,  0,  0)

   ***************************************************************************/

  int **table = matrix( 15, 2 );
  int table_col[15] = {1, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34};
  int table_row[7] = {3, 11, 19, 27, 35, 43, 51};

  int col, row;
  getmaxyx(stdscr, col, row);

  if( row % 2 == 0 )
  {
    row = abs(row - 62 ) / 2;
  }
  else
  {
    row = abs(row - 61 ) / 2;
  }


  if( col % 2 == 0 )
  {
    col = abs( col - 32 ) / 2;
  }
  else
  {
    col = abs( col - 31 ) / 2;
  }


  for( int i = 0; i < 15; i++ )
  {
    table[i][0] = table_col[i] + col;
  }

  for( int i = 0; i < 7; i++ )
  {
    table[i][1] = table_row[i] + row;
  }
  return table;
}


int ***set_tableau( int **coordinates, int **deck)
{
    int ***tableau  = multi_dimensional( 7, 15, 5 );
    int z = 0;
    /****************************************************************************
     * Looks for a change in screen size, then manipulates the table matrix
   * accordingly to ensure everything is centered.
   *
   *TABLE MATRIX (BEFORE MANIPULATION):
   *table[i][0] (col: 1,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34)
   *table[i][1] (row: 3, 11, 19, 27, 35, 43, 51,  0,  0,  0,  0,  0,  0,  0,  0)

   ***************************************************************************/


  for( int x = 0; x < 7; x++ )
  {
    for( int y = 0; y < 15; y++ )
    {
      if( x >= y )

      {
        tableau[x][y][0] = deck[z][0];      /* Card Value */
        tableau[x][y][1] = deck[z][1];      /* Card Suite */

        if( x == y )
        {
          tableau[x][y][2] = 1;   /* Show card face?  */
        }                         /* 0 = no           */
                                  /* 1 = yes          */
                                  /* 2 = clicked      */
                                  /* 3 = non-existent */
        else
        {
          tableau[x][y][2] = 0;
        }

        tableau[x][y][3] = coordinates[y+1][0];   /*    col     */
        tableau[x][y][4] = coordinates[x][1];     /*    row     */
        z++;
      }
      else
      {
        tableau[x][y][0] = 0;   /*    Value   */
        tableau[x][y][1] = 0;   /*    Suite   */
        tableau[x][y][2] = 3;   /* Card Attr. */
        tableau[x][y][3] = 0;   /*     col    */
        tableau[x][y][4] = 0;   /*     row    */
        /* NOTE: 0 denotes "no" and 1 denotes "yes"; when the 3D=2 (Show Card)
         * aditional options are as follows:clicked(2) & non-existent(3) ) */
      }
    }
  }

  return tableau;
}


int **shuffle_deck( void )
/* shuffles deck then returns value as a matrix                             */
{
    int of_a_kind = 0, redo = 0;
    int **deck = matrix( 52, 2 );
    /* int deck[52][2]; first row determines card value, second row determines
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


pile *set_stock( int **deck, pile *head )
{
  pile *new_link = NULL;
  pile *stock = NULL;

  for( int i = 28; i < 52; i++ )
  {
    new_link = malloc(sizeof(pile));
    if( i == 28 )
    {
      new_link->value =  0;
      new_link->suite =  0;
    }
    else
    {
      new_link->value =  deck[i][0];
      new_link->suite =  deck[i][1];
    }
    if( i == 51 )
    {
      new_link->next = head;
    }
    else
    {
      new_link->next = NULL;
    }

    if( head == NULL )
    {
      head = new_link;
    }
    else
    {
      stock = head;
      while( stock->next != NULL )
      {
        stock = stock->next;
      }
      stock->next = new_link;
    }

  }
  return head;
}

