/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      getHostID.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @brief     Get the system host ID, and display it to STDOUT@EOL
   @Keywords  gethostid sysctl
   @Std       C99

   This function probably should not be used on many systems in preference for sysctl; however, this function generally works on
   more platforms.
***********************************************************************************************************************************/

#include <unistd.h>             /* UNIX std stf    POSIX */
#include <stdio.h>              /* I/O lib         C89   */

/**********************************************************************************************************************************/
int main() {
  long unsigned int hostID;
  hostID = gethostid();
  printf("Host ID: %lx\n", (long unsigned int)hostID);
  return 0;
} /* end func main */
