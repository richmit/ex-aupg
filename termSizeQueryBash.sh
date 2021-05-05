#!/bin/bash
# -*- Mode:Shell-script; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      termSizeQueryBash.sh
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1994,1996,2008 by Mitch Richling.  All rights reserved.
# @brief     Get the terminal size with bash.@EOL
# @Keywords  terminal size bash 
# @Std       Bash
#
# This is a reasonably reliable way to get the terminal width when using bash in interactive mode.  Note that this script must be
# "sourced" in order to work -- the shell needs to be "interactive":
#
#    $> . termSizeQueryBash.sh
#       ^
#       |
#       + Note the "." -- that is how you "source" in bash!
#
# Note that with bash we can just use $LINES and $COLUMNS in interactive shell sessions.

##----------------------------------------------------------------------------------------------------------------------------------

if echo "$LINES" | grep '^[0-9][0-9]*$' >/dev/null ; then
    echo "$LINES x $COLUMNS"
else
    echo "ERROR: Could not figure out term size"
fi
