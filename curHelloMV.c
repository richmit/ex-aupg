/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      curHelloMV.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1999 by Mitch Richling.  All rights reserved.
   @brief     Demonstrates the ncurses mvprintw function@EOL
   @Keywords  ncurses
   @Std       C89

   Minimal ncurses program demonstrating mvprintw.
***********************************************************************************************************************************/

#include <ncurses.h>            /* Popular Curses  ????  */

/**********************************************************************************************************************************/
int main() {
  initscr();                                                 /* Initialize curses (the SCReen)               */
  mvprintw(10, 40, "Hello, World! (press any key to quit)"); /* Print "Hello, World!" to 'stdscr' at (40,10) */
  refresh();                                                 /* Draw 'stdscr' on the real screen             */
  getch();                                                   /* Wait for a key press                         */
  endwin();                                                  /* Shutdown curses                              */
  return 0;                                                  /* We are done, time to exit.                   */
} /* end func main */
