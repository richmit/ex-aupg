#!/bin/sh
# -*- Mode:Shell-script; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      termSizeQuerySYSV.sh
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1994,1996,2008 by Mitch Richling.  All rights reserved.
# @brief     Get the terminal size on SysV-like systems with a shell script.@EOL
# @Keywords  terminal size width system v sysv shell
# @Std       Bourne
#
# This is a reasonably reliable way to get the terminal width on SysV-like systems (Linux, Solaris, etc...) with little more than a
# standard Bourne shell and a few standard shell utilities (grep, sed, and stty).

##----------------------------------------------------------------------------------------------------------------------------------

# Linux & SYSV-like

TERMWIDE=`stty -a | sed -n 's/.*columns \([0-9][0-9]*\);.*$/\1/p'`

if echo "$TERMWIDE" | grep '^[0-9][0-9]*$' >/dev/null ; then
    echo "$TERMWIDE"
    exit
fi
