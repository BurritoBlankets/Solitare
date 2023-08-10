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

#include "functions.h"      /* solitaire functions                          */

void prerequisites( void )
  /* Checks for terminal size and color support */
{
  int col, row;
  getmaxyx(stdscr, col, row);
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
  if(  col < 27 || row < 62 )
  {
    endwin();
    printf("ERROR: Terminal is too small (required: 62x27); ");
    printf("Current size: %dx%d\n", row, col );
    exit(1);
  }
}


void print_background( void )
{
  int col, row;
  getmaxyx(stdscr, col, row);

  WINDOW * background = newwin( col, row, 0, 0 );

  wbkgd( background, COLOR_PAIR(4) );  /* card outline  */
  box( background, 0, 0 );

  touchwin( background );
  wrefresh( background );
  endwin();
}


void print_foundations( int **coordinates )
{
  for( int i = 3; i < 7; i++ )
  {
    WINDOW *card = newwin( 6 , 8 , coordinates[0][0] , coordinates[i][1] );
    wattron( card, COLOR_PAIR(1) );  /* card outline  */
    wbkgd(card, COLOR_PAIR(1));
    box( card, 0, 0 );
    touchwin( card );
    wrefresh( card );
  }
}


void print_stock( int **coordinates, int **deck, int value, int suite)
{
  WINDOW *stock_hide = newwin( 6 , 8 , coordinates[0][0] , coordinates[0][1] );
  WINDOW *stock_show = newwin( 6 , 8 , coordinates[0][0] , coordinates[1][1] );

    if( value != deck[51][0] || suite != deck[51][1])
    {
      box( stock_hide, 0, 0 );
      wbkgd( stock_hide, COLOR_PAIR(1) );  /* card outline  */
      wattrset( stock_hide, COLOR_PAIR( 5 ) );
      for( int i = 1; i < 5; i++ )
      {
        mvwprintw( stock_hide, i, 1, "XXXXXX");
      }
      touchwin( stock_hide );
      wrefresh( stock_hide );
    }

    if( value != 0 )
    {
      wattrset( stock_show, COLOR_PAIR(1) );  /* card outline  */
      box( stock_show, 0, 0 );
      print_card( stock_show, value, suite, 1, 1 );
      touchwin( stock_show );
      wrefresh( stock_show );

    }
  }


void print_tableau(int ***tableau )
{
  //char suite_arracol[] = "♥️♦️♣️♠️"; ncurses != emoji support

  for( int row = 0; row < 7; row++ )
  {
    for( int col = 0; col < 15; col++ )
    {

      if( tableau[row][col][2] == 1 ||  tableau[row][col][2] == 2 )
      {/* if card is shown or clicked... */

      WINDOW *card = newwin( 4 , 6 ,tableau[row][col][3]-col, tableau[row][col][4]+1 );

        print_card( card, tableau[row][col][0], tableau[row][col][1], tableau[row][col][2], 0 );
        touchwin( card );
        wrefresh( card );

      }
      else if( tableau[row][col][2] == 0 )
      {
        WINDOW *card = newwin( 1 , 6 ,tableau[row][col][3]-col, tableau[row][col][4]+1 );
        wattrset( card, COLOR_PAIR(1) );  /* card outline  */
        wattrset( card, COLOR_PAIR( 5 ) );
        box( card, 0, 0 );
        touchwin( card );
        wrefresh( card );

      }
    }
  }
}
