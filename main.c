/******************************************************************************
* File:    main.c
 * Author:  Pillo Duenas-Lopez
 * Version: 0.0 (JUN, 01, 2023)
 *
 * Purpose:
 *          Terminal playable solitaire
 *          1) center game
 *          3) create button
 *
 * Notes:

 *          3. make linked list, utilize for loop to store extra cards
 *
 *          **table[col][row]       // matrix coordinates               //
 *          4. print tableau to screen utilizing **table for card placement
 *              if( tableau[x][y][0] == 0 );{ don't print }
 *
 *          Foundation 1-4          // linked list, sorts each suite    //
 *
 *****************************************************************************/

#include "functions.h"      /* graphics.c functions                         */
#include <curses.h>

int main( void )
{
  setlocale(LC_CTYPE,"C-UTF-8");
  initscr();
  prerequisites();

  srand( time( NULL ) );
  int **deck = shuffle_deck( );

  pile *stock = NULL;
  stock = set_stock( deck, stock );

  int **coordinates = placement_refresh();

  int ***tableau  = set_tableau( coordinates, deck) ;
  /* FIX THIS LOGIC LEADING TO SEG FAULT ^^^*/


  init_pair( 1, COLOR_WHITE, COLOR_GREEN);
  init_pair( 2, COLOR_BLACK, COLOR_WHITE );
  init_pair( 3, COLOR_RED, COLOR_WHITE );
  init_pair( 4, COLOR_GREEN, COLOR_GREEN );
  init_pair( 5, COLOR_WHITE, COLOR_RED );
  init_pair( 6, COLOR_GREEN, COLOR_WHITE );
  init_pair( 7, COLOR_YELLOW, COLOR_WHITE );

  int ch;
  MEVENT new_event;

  mousemask( BUTTON1_PRESSED | REPORT_MOUSE_POSITION, NULL );
  keypad( stdscr, TRUE ); /* enables use of arrows                */
  cbreak();               /* disables need for carriage return    */
  noecho();               /* disables auto-echoing                */

  while( true )
  {
    coordinates = placement_refresh();
    print_background();
    print_stock( coordinates, deck, stock->value, stock->suite );
    print_foundations( coordinates );
    print_tableau(tableau);

    ch = wgetch( stdscr );
    if( ch == KEY_MOUSE )
    {
      getmouse( &new_event );
      if( new_event.y >= coordinates[0][0]          /* if stock card is pressed... */
          && new_event.y <= coordinates[0][0]+6
          && new_event.x >= coordinates[0][1]
          && new_event.x <= coordinates[0][1]+8
        )
      {
        stock = stock->next;
      }
      else
      {
        mvwprintw(stdscr, 0,0,"event.y = %d; event.x = %d", new_event.y, new_event.x);
        mvwprintw(stdscr, 1,0,"event.y = %d; event.x = %d", tableau[1][1][3], tableau[1][1][4]+1);
        tableau_click( tableau, new_event );
      }
    }


  }
  endwin();
  free_matrix( deck, 52 );
  free_matrix( coordinates, 15  );
  free_dimensions( tableau, 7, 20 );
  return 0;
}
