/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      semMake.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1998 by Mitch Richling.  All rights reserved.
   @brief     How to create/use a shared memory segment@EOL
   @Keywords  UNIX shared memory
   @Std       ISOC
   @Tested    
              - Solaris 2.8
              - MacOS X.2
              - Linux (RH 7.3)

   This C program is intended to illustrate how one can create/access shared memory segments in UNIX using the system V APIs
   (POSIX.1 XSI APIs).
***********************************************************************************************************************************/

#include <stdlib.h>             /* Standard Lib    C89   */
#include <stdio.h>              /* I/O lib         C89   */
#include <string.h>             /* Strings         C89   */
#include <unistd.h>             /* UNIX std stf    POSIX */
#include <errno.h>              /* error stf       POSIX */
#include <sys/stat.h>           /* UNIX stat       POSIX */
#include <sys/types.h>          /* UNIX types      POSIX */
#include <sys/ipc.h>            /* Need for IPC    POSIX */
#include <sys/sem.h>            /* Semaphores      POSIX */

/**********************************************************************************************************************************/
int main() {
  int semId;
  void *semAdd;
  key_t semKey;

  /* ftok is a handy way to generate a shared memory segment key (or a semaphore key).  On most platforms it works by using the
     inode of the path given as the first arg -- so it will only be unique if the path used by all applications is on the same
     volume (as inodes can be duplicated across different volumes).  For this reason it has become the de facto standard practice to
     use /tmp (or a file in /tmp) to generate keys...  Note: always use a single byte char for the second argument. */
  semKey = ftok("/tmp", 'j');
  if (semKey < 0) {
    switch(errno) {
      case EACCES:       printf("ftok failed: Search permission denied for a component of the path prefix.\n");
        break;
      case ELOOP:        printf("ftok failed: A loop exists in symbolic links in path argument or too many symlinks found.\n");
        break;
      case ENAMETOOLONG: printf("ftok failed: The length of path exceeds {PATH_MAX} or pathname component longer than {NAME_MAX}.\n");
        break;
      case ENOENT:       printf("ftok failed: A component of path does not name an existing file or path is an empty string.\n");
        break;
      case ENOTDIR:      printf("ftok failed: A component of the path not a directory.\n");
        break;
      default:           printf("ftok failed: Duno why! (errno: %d)\n", errno);
        break;
    } /* end switch */
    exit(1);
  } /* end if */

  /* We get a semaphore ID for our key.  IPC_CREAT tells semget to create a semaphore, and IPC_EXCL makes semget fail if the key is
     already in use.  The 0777 sets the perms of the segment (just like a disk file). */
  semId = semget(semKey, 1, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if(semId < 0) {
    /* I have a case for all of the interesting cases, even the ones that can not happen in this situation... */
    switch(errno) {
      case EACCES:  printf("key in use, but operation permission could not be granted\n");
        break;
      case EEXIST:  printf("key in use, but ((semflg &IPC_CREAT) &&(semflg &IPC_EXCL)) non-zero.\n");
        break;
      case EINVAL:  printf("nsems out of range, or key exists and has fewer than requested semaphores.\n");
        break;
      case ENOENT:  printf("Key not in use, and (semflg &IPC_CREAT) is equal to 0.\n");
        break;
      case ENOSPC:  printf("Can not make any more semaphores (too many already).\n");
        break;
      default:      printf("semget failed: Duno why! (errno: %d)\n", errno);
        break;
    } /* end switch */
    exit(1);
  } /* end if */
  printf("semget result: %d\n", semId);

  // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  /* Finish this up.... */
  // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

  return 0;
} /* end func main() */
