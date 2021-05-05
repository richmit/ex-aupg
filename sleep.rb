#!/home/richmit/bin/verGo.sh ruby
# -*- Mode:Ruby; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      sleep.rb
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 2011 by Mitch Richling.  All rights reserved.
# @brief     Ruby and sleeping@EOL
# @Keywords  sleep signal ruby
# @Std       Ruby1.8.1
#
# Unlike Perl and C, the Ruby sleep() call will really sleep through signals.  So this example is super simple compared to the C and
# Perl versions.

##----------------------------------------------------------------------------------------------------------------------------------

secToSleep = 600;

# Setup a signal handler so we can test with SIGUSR1 signals
sigIntHand = proc { puts("SIG RECV: SIGUSR1") }
Signal.trap("SIGUSR1", sigIntHand)
puts("My PID(try SIGUSR1): #{Process.pid}")

startTime = Time.now

# Loop until we have waited secToSleep seconds.
sleep(secToSleep)

puts("Time gone by: #{Time.now - startTime}")
