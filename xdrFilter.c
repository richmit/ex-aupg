/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      xdrFilter.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1998,2005 by Mitch Richling.  All rights reserved.
   @brief     Short XDR filter example@EOL
   @Keywords  xdr unix hdf5
   @Std       C99

   This little example shows how to convert the native binary format of various C data types into an architecture independent form
   using the xdr (external data representation) library available on most UNIX systems.  The most typical application of XDR is to
   transform data into a machine neutral form for transmission across a network (RPC calls for example), or to write files that are
   compatible with different hardware platforms.

   In scientific circles, this library is almost never use anymore.  Generally speaking, products like HDF5 have filled this need
   quite neatly.  XDR is still quite common in network applications and system level code.

   While xdr_float is the only filter function demonstrated, many filter functions exist for the various atomic data types.  Support
   also exists, but is not commonly used, for compound data types (structs), arrays, c-strings, and pointers.  XDR has several
   additional functions exist that make reading/writing from files, stdin/stdout, and sockets very easy.

   The most commonly seen filter functions are:

      - xdr_double(xdrs, dp)
      - xdr_float(xdrs, fp)
      - xdr_int(xdrs, ip)
      - xdr_long(xdrs, lp)
      - xdr_short(xdrs, sp)
      - xdr_char(xdrs, cp)
      - xdr_u_char(xdrs, ucp)
      - xdr_u_int(xdrs, up)
      - xdr_u_long(xdrs, ulp)
      - xdr_u_short(xdrs, usp)
***********************************************************************************************************************************/

#include <rpc/rpc.h>            /* SUN RPC (XDR)   POSIX */
#include <stdio.h>              /* I/O lib         C89   */
#include <stdlib.h>             /* Standard Lib    C89   */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
  XDR           xdrs;
  char          xdrMem[1024];
  unsigned int  len = 1024;
  float         dp1 = 1.2345;
  float         dp2 = 0.0;
  unsigned char *cp;
  int           i;
  
  /* First we create an xdr memory stream -- to hold our data. */
  xdrmem_create(&xdrs, xdrMem, len, XDR_ENCODE);

  /* Now we write a float into it. */
  xdr_float(&xdrs, &dp1);

  /* Now we set the stream to decode, reset the location to the beginning, and read a float from it. */
  xdrs.x_op = XDR_DECODE;
  xdr_setpos(&xdrs, 0);
  xdr_float(&xdrs, &dp2);

  /* Print out the bytes of the original float. */
  printf("%2d bytes of float: ", (int)sizeof(float));
  for(cp=(unsigned char *)&dp1, i=0; i<sizeof(float); i++) {
    printf("%02x ", (unsigned int)cp[i]);
  } /* end for */
  printf("\n");

  /* Print out 32 bytes of the XDR stream */
  printf("32 bytes of XDR:   ");
  for(cp=(unsigned char *)&xdrs, i=0; i<32; i++) {
    printf("%02x ", (unsigned int)cp[i]);
  } /* end for */
  printf("\n");

  /* Print out the floats we wrote into and read from the XDR stream */
  printf(" Starting Float:   %f\n", dp1);
  printf("   Ending Float:   %f\n", dp2);

  /* We are done. */
  return 0;
} /* end func main */
