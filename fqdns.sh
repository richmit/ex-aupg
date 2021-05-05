#!/bin/sh
# -*- Mode:Shell-script; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      fqdns.sh
# @author    Mitch Richling <https://www.mitchr.me>
# @Copyright Copyright 1998 by Mitch Richling.  All rights reserved.
# @brief     How to get a host's FQDNS.@EOL
# @Keywords  fqdns hostname unix
# @Std       bash Bourne POSIX1003.2
#
# Determining the fully qualified host name of a UNIX host from it's 'hostname' can be a bit of a challenge.  In fact, it is just
# about impossible to do from the shell in a standards based way.  This script is a best effort attempt, but if you really need it
# to work, then use a Perl script or C program!
#
# Most of the system software is designed to have the host name be simple ('foo' and not 'foo.bar.com').  Nothing breaks if it is
# fully qualified, and this is common practice with modern system administrators.  This script attempts to do the right thing in
# both cases and it makes use of some non-traditional and non-standard techniques that generally work relatively well in practice.
#            

##----------------------------------------------------------------------------------------------------------------------------------

PATH=/bin:/usr/bin:$PATH
export PATH

# If the hostname has a '.', then we assume it is FQDNS as the RFCs indicate that a simple host name hostname may not contain a '.'.
HOSTNAME=`hostname`
if echo $HOSTNAME | grep '\.' >/dev/null; then
   echo $HOSTNAME
   exit
fi

# We try to use nslookup on the host name.  If we get a result we print it out and quit.  Note that newer versions of nslookup print
# a warning.  You can use 'host' or 'dig' if this is the case on systems you support.
RESOUT=`nslookup $HOSTNAME| sed -n 's/Name: *//p'`
if echo $RESOUT | grep '\.' >/dev/null; then
   echo $RESOUT
   exit
fi

# Well, gee wiz, now we look in resolv.conf and try to find a domain name that way.  This may do very bad things if you have strange
# resolv.conf files in your network..
if test -e /etc/resolv.conf; then
   if grep domain /etc/resolv.conf; then
      echo `hostname`.`tr -s '[:space:]' ' ' </etc/resolv.conf  | sed -n 's/^domain *//p'`
      exit
   fi
fi

# Well, we couldn't figure it out.  We just return the simple name:
echo $HOSTNAME
