#!/bin/sh
# -*- Mode:Shell-script; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      termSizeQueryBSD.sh
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1994,1996,2008 by Mitch Richling.  All rights reserved.
# @brief     Get the terminal size on BSD-like systems with a shell script.@EOL
# @Keywords  terminal size width BSD shell
# @Std       Bourne
#
# This is a reasonably reliable way to get the terminal width on BSD-ish (FreeBSD, OpenBSD, Darwin, NetBSD, SunOS 4.x, etc...) with
# little more than a standard Bourne shell and a few standard shell utilities (grep, sed, and stty).

##----------------------------------------------------------------------------------------------------------------------------------

TERMWIDE=`stty -a | sed -n 's/.*; *\([0-9][0-9]*\) columns;.*$/\1/p'`
TERMTALL=`stty -a | sed -n 's/.*; *\([0-9][0-9]*\) rows;.*$/\1/p'`

if echo "$TERMWIDE" | grep '^[0-9][0-9]*$' >/dev/null ; then
    echo "$TERMTALL x $TERMWIDE"
else
    echo "ERROR: Could not figure out term size"
fi
