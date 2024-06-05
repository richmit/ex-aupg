

/* This one is in work.  It is not finished yet.  Just playing around. */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 1024
#endif

int
main()
{
  struct addrinfo hints, *result, *rp;
  int s;

  char hostName[MAXHOSTNAMELEN];

  if(gethostname(hostName, MAXHOSTNAMELEN)) {
    printf("ERROR: Could not get hostname\n");
    exit(1);
  } /* end if */

  printf("HOSTNAME: %s\n", hostName);

  
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family    = AF_INET;
  hints.ai_flags     = AI_CANONNAME;

  s = getaddrinfo(hostName, NULL, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    if(rp->ai_canonname) 
      printf("CANONNAME: %s\n", rp->ai_canonname);
  }

  freeaddrinfo(result);           /* No longer needed */
}
