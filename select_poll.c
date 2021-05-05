/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      select_poll.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1993 by Mitch Richling.  All rights reserved.
   @brief     The UNIX select and poll functions.@EOL
   @Keywords  UNIX I/O file select timeout poll
   @Std       ISOC 
   @Tested    
              - Solaris 2.8
              - MacOS X.2
              - Linux (RH 7.3)
   
   This C program is intended to illustrate how one can use the select(2) function to determine if a particular file descriptor has
   data to read or has an error condition without using a read(2) system call.  This is a very useful technique for network
   programming as well.  We use the select because it is a bit more portable.

   Note that select on some platforms is limited to 1024 FDs.  64-bit Solaris has a much higher limit.  MacOS X allows this limit to
   be increased via a define.
***********************************************************************************************************************************/

#include <stdio.h>              /* I/O lib         C89   */
#include <stdlib.h>             /* Standard Lib    C89   */
#include <sys/types.h>          /* UNIX types      POSIX */
#include <sys/time.h>           /* UNIX time       ????  */
#include <unistd.h>             /* UNIX std stf    POSIX */
#include <errno.h>              /* error stf       POSIX */
#include <string.h>             /* Strings         C89   */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {

  fd_set readFds, exceptFds;
  struct timeval theTimeOut;

  while(1) {
    /* First we must empty(zero out) the file descriptor sets. */
    FD_ZERO(&readFds);
    FD_ZERO(&exceptFds);

    /* Next we populate the file descriptors sets with the file descriptors we are interested in. */
    FD_SET(STDIN_FILENO, &readFds);
    FD_SET(STDIN_FILENO, &exceptFds);

    /* select will not modify the timeout argument, but it is good form to reset it before each call to select(2).  The zero values
       makes select act like poll. */
    theTimeOut.tv_sec = 0;
    theTimeOut.tv_usec = 0;

    /* Finally, we can call the select function!  Note that the third argument is NULL.  This tells select we don't care if the
       descriptor is ready to receive data (it is standard in after all). */
    if(select(1, &readFds, NULL, &exceptFds, &theTimeOut) < 0) {
      perror("ERROR: Select");
      exit(1);
    } /* end if */

    /* Check to see if data is available for read. */
    if(FD_ISSET(STDIN_FILENO, &readFds))
      printf("STDIN has data to read...\n");
    else
      printf("STDIN has NO data to read...\n");

    /* Now check to see if the file descriptor has an error. */
    if(FD_ISSET(STDIN_FILENO, &exceptFds))
      printf("STDIN has some sort of error...\n");

    /* We sleep for a second.  This is dumb, because we could have simply set a timeout of 1 on the select call.  We don't do that
       because this program is demonstrateing how to use select(2) instead of poll(2) */
    sleep(1);

  } /* end while */
} /* end func main */
