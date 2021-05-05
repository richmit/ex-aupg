/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      sysconf.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1999 by Mitch Richling.  All rights reserved.
   @brief     UNIX sysconf function@EOL
   @Keywords  UNIX sysconf POSIX
   @Std       POSIX ISOC
   @Tested    
              - Solaris 2.8
              - MacOS 10.3, 10.9.5
              - Linux (RH 7.3, Debian 8.0)

debiandebiandebian



   This is an example program intended to illustrate how to use sysconf to get various system parameters.  POSIX defines many
   constants for use as the argument to sysconf; however, many systems don't implement them all.  The constants demonstrated in this
   program represent some useful constants that are defined by many UNIX variants.
***********************************************************************************************************************************/

#include <unistd.h>             /* UNIX std stf    POSIX */
#include <stdio.h>              /* I/O lib         C89   */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {

#ifdef _SC_ARG_MAX
  printf("_SC_ARG_MAX .......... Maximum bytes of argument to execve ................... %d\n", (int)sysconf(_SC_ARG_MAX));           // POSIX.1
#endif
#ifdef _SC_CHILD_MAX
  printf("_SC_CHILD_MAX ........ Maximum number of simultaneous processes per user id .. %d\n", (int)sysconf(_SC_CHILD_MAX));         // POSIX.1
#endif
#ifdef _SC_HOST_NAME_MAX
  printf("_SC_HOST_NAME_MAX .... Maximum length of host name ........................... %d\n", (int)sysconf(_SC_HOST_NAME_MAX));     // POSIX.1
#endif
#ifdef _SC_LOGIN_NAME_MAX
  printf("_SC_LOGIN_NAME_MAX ... Maximum number of simultaneous processes per user id .. %d\n", (int)sysconf(_SC_LOGIN_NAME_MAX));    // POSIX.1
#endif
#ifdef _SC_CLK_TCK
  printf("_SC_CLK_TCK .......... Frequency of the statistics clock in ticks per second . %d\n", (int)sysconf(_SC_CLK_TCK));           // POSIX.1
#endif
#ifdef _SC_OPEN_MAX
  printf("_SC_OPEN_MAX ......... Maximum number of open files per user id .............. %d\n", (int)sysconf(_SC_OPEN_MAX));          // POSIX.1
#endif
#ifdef _SC_PAGESIZE
  printf("_SC_PAGESIZE ......... Size of a page in bytes ............................... %d\n", (int)sysconf(_SC_PAGESIZE));          // POSIX.1
#endif
#ifdef _SC_NGROUPS_MAX
  printf("_SC_NGROUPS_MAX ...... Maximum number of supplemental groups ................. %d\n", (int)sysconf(_SC_NGROUPS_MAX));       // ???
#endif
#ifdef _SC_VERSION
  printf("_SC_VERSION .......... Version of POSIX.1 with for system .................... %d\n", (int)sysconf(_SC_VERSION));           // POSIX.1
#endif
#ifdef _SC_2_VERSION
  printf("_SC_2_VERSION ........ Version of POSIX.2 with for system .................... %d\n", (int)sysconf(_SC_2_VERSION));         // POSIX.2
#endif
#ifdef _SC_STREAM_MAX
  printf("_SC_STREAM_MAX ....... Minimum maximum number of streams per process ......... %d\n", (int)sysconf(_SC_STREAM_MAX));        // POSIX.1
#endif
#ifdef _SC_PAGESIZE
  printf("_SC_PAGESIZE ......... Memory page size of the system expressed in bytes ..... %d\n", (int)sysconf(_SC_PAGESIZE));          // POSIX.1
#endif
#ifdef _SC_SAVED_IDS
  printf("_SC_SAVED_IDS ........ Saved SGID & SUID available (1 is YES, -1 is NO) ...... %d\n", (int)sysconf(_SC_SAVED_IDS));         // ???
#endif
#ifdef _SC_SYMLOOP_MAX
  printf("_SC_SYMLOOP_MAX ...... Maximum number of symbolic links in a path ............ %d\n", (int)sysconf(_SC_SYMLOOP_MAX));       // POSIX.1
#endif
#ifdef _SC_TTY_NAME_MAX
  printf("_SC_TTY_NAME_MAX ..... Maximum number characters in TTY device name .......... %d\n", (int)sysconf(_SC_TTY_NAME_MAX));      // POSIX.1
#endif
#ifdef _SC_2_C_DEV
  printf("_SC_2_C_DEV .......... POSIX.2 C language development facilitiessupported .... %d\n", (int)sysconf(_SC_2_C_DEV));           // POSIX.2
#endif
#ifdef _SC_2_FORT_DEV
  printf("_SC_2_FORT_DEV ....... POSIX.2 FORTRAN development utilities supported ....... %d\n", (int)sysconf(_SC_2_FORT_DEV));        // POSIX.2
#endif
#ifdef _SC_2_FORT_RUN
  printf("_SC_2_FORT_RUN ....... POSIX.2 FORTRAN run-time utilities supported .......... %d\n", (int)sysconf(_SC_2_FORT_RUN));        // POSIX.2
#endif
#ifdef _SC_2_SW_DEV
  printf("_SC_2_SW_DEV ......... POSIX.2 software development utilities supported ...... %d\n", (int)sysconf(_SC_2_SW_DEV));          // POSIX.2
#endif
#ifdef _SC_PHYS_PAGES
  printf("_SC_PHYS_PAGES ....... Number of pages of physical memory .................... %d\n", (int)sysconf(_SC_PHYS_PAGES));        // NON-STD
#endif
#ifdef _SC_AVPHYS_PAGES
  printf("_SC_AVPHYS_PAGES ..... Number of available pages of physical memory .......... %d\n", (int)sysconf(_SC_AVPHYS_PAGES));      // NON-STD
#endif
#ifdef _SC_NPROCESSORS_CONF
  printf("_SC_NPROCESSORS_CONF . Number of processors configured ....................... %d\n", (int)sysconf(_SC_NPROCESSORS_CONF));  // NON-STD
#endif
#ifdef _SC_NPROCESSORS_ONLN
  printf("_SC_NPROCESSORS_ONLN . Number of processors available ........................ %d\n", (int)sysconf(_SC_NPROCESSORS_ONLN));  // NON-STD
#endif
#ifdef _SC_GETGR_R_SIZE_MAX
  printf("_SC_GETGR_R_SIZE_MAX . Get GR Max ............................................ %d\n", (int)sysconf(_SC_GETGR_R_SIZE_MAX));  // POSIX 1003.1c threads
#endif
#ifdef _SC_GETPW_R_SIZE_MAX
  printf("_SC_GETPW_R_SIZE_MAX . Get PW Max ............................................ %d\n", (int)sysconf(_SC_GETPW_R_SIZE_MAX));  // POSIX 1003.1c threads
#endif
#ifdef _SC_LOGIN_NAME_MAX
  printf("_SC_LOGIN_NAME_MAX ... Login Name Max ........................................ %d\n", (int)sysconf(_SC_LOGIN_NAME_MAX));    // POSIX 1003.1c threads
#endif
#ifdef _SC_XOPEN_VERSION
  printf("_SC_XOPEN_VERSION .... XOpen Version ......................................... %d\n", (int)sysconf(_SC_XOPEN_VERSION));    // ???
#endif
  return 0;
} /* end func main */
