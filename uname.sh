#!/bin/sh
# -*- Mode:Shell-script; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      uname.sh
# @author    Mitch Richling<https://www.mitchr.me/>
# @Copyright Copyright 1998 by Mitch Richling.  All rights reserved.
# @brief     Example of how to use the /usr/bin/uname command.@EOL
# @Keywords  
# @Std       Bourne

##----------------------------------------------------------------------------------------------------------------------------------

echo "sysname(-s):  " `/usr/bin/uname -s`
echo "nodename(-n): " `/usr/bin/uname -n`
echo "release(-r):  " `/usr/bin/uname -r`
echo "version(-v):  " `/usr/bin/uname -v`
echo "machin(-m):   " `/usr/bin/uname -m`
