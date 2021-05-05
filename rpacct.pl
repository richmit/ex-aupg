#!/usr/local/bin/perl
# -*- Mode:Perl; Coding:us-ascii-unix; fill-column:132 -*-

####################################################################################################################################
# @file      rpacct.pl
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1998 by Mitch Richling.  All rights reserved.
# @brief     How to parse System V accounting files@EOL
# @Keywords
# @Std       Perl5
#
# This program is intended to read and parse a process accounting file generated by a SVR4 system like Solaris.
#
# The 'acct' struct contains:
#   char     ac_flag;     Accounting flag
#   char     ac_stat;     Exit status
#   uid32_t  ac_uid;      Accounting user ID
#   gid32_t  ac_gid;      Accounting group ID
#   dev32_t  ac_tty;      control typewriter
#   time32_t ac_btime;    Beginning time
#   comp_t   ac_utime;    acctng user time in clock ticks
#   comp_t   ac_stime;    acctng system time in clock ticks
#   comp_t   ac_etime;    acctng elapsed time in clock ticks
#   comp_t   ac_mem;      memory usage
#   comp_t   ac_io;       chars transferred
#   comp_t   ac_rw;       blocks read or written
#   char     ac_comm[8];  command name
#
# comp_t is a 16-bit fixed point number.  A 3-bit exponent in the high order bits, and a 13-bit fraction in the low order bits.
# uid32_t, gid32_t, time32_t are all 32-bit integers.  char is an 8-bit quantity.
#
# Decoding the comp_t type:
#
# This is a very compact expression for a floating point number. The floating point number hidden with a member $foo of comp_t type
# may be extracted with: ($foo & 8191) * (8 ** ($foo >> 13))
#
# A process accounting file is a file full of 'acct' structs.  Thus we can read the data in blocks that are the size of an acct
# struct and then break the blocks up into the parts we are interested in.  From the sizes and types of the structure components we
# should be able to use a format string of ccLLLLSSSSSSA8 to unpack this data structure, but we have an alignment problem.  We have
# an extra two bytes stuck between the ac_stat member and the ac_uid member.  It is ironic that such a carefully constructed data
# structure designed to conserve space has a hole in it. :) The format string we must us is ccc2LLLLSSSSSSA8
#
# Meaning of the members:
#   - ac_utime, ac_stime, ac_etime are all in clock ticks.  For SPARC Solaris this is 100.
#   - ac_btime is the time the process started.  It is expressed as the standard UNIX time number stored in a 32-bit quantity.
#   - ac_mem is a strange one.  Each tick, the OS updates this value with (data_size + text_size) /
#     (number_of_in-core_processes_using_text) Thus ac_mem/(ac_stime+ac_utime) is a measure of the average memory used.  This is in
#     pages.  So you have to know the page size of the host the process accounting file came from.
#   - ac_flags is a flag quantity.  The bit at 01 means the thing forked but did not exec.  The bit at 02 means that the program ran
#     with UID 0 privileges.

##----------------------------------------------------------------------------------------------------------------------------------

$TICKSPERSEC = 100.0;
$PAGESIZE = 8.0;

printf("%-10s %-10s %-10s %20s %20s %12s %12s %12s %10s %12s %15s %5s %5s\n",
       'Command', 'User', 'Group', 'Start_Time', 'End_Time', 'Run_Sec', 'Usr_CPU', 'Sys_CPU', 'RAM', 'Blk_I/O', 'Char_I/O', 'Exit', 'Flags');
printf("%-10s %-10s %-10s %20s %20s %12s %12s %12s %10s %12s %15s %5s %5s\n",
       '', '', '', 'Local', 'Local', 'Sec', 'Sec', 'Sec', 'Kbytes', 'Blocks', 'Bytes', 'Dec', '');
open(FP, "<$ARGV[0]") || die "ugh\n";
while($numRead = read(FP,$data,40)) {
  if($numRead = 40) {
    # Unpack the structure into variables.
    ($ac_flag, $ac_stat, $junk, $junk, $ac_uid, $ac_gid, $ac_tty, $ac_btime, $ac_utime, 
     $ac_stime, $ac_etime, $ac_mem, $ac_io, $ac_rw, $ac_comm) = unpack("ccc2LLLLSSSSSSA8", $data);
    # Get uname
    $ac_uname = getpwuid($ac_uid);
    #Get group name
    $ac_grp = getgrgid($ac_gid);
    # Get start date
    ($st_sec, $st_min, $st_hour, $st_mday, $st_mon, $st_year, $st_wday, $st_yday, $st_isdst) = localtime($ac_btime);
    $st_date = sprintf("%4d-%02d-%02d_%02d:%02d:%02d", $st_year+1900, $st_mon+1, $st_mday, $st_hour, $st_min, $st_sec);
    #Get real time
    $etime_real = ($ac_etime & 8191) * (8 ** ($ac_etime >> 13)) / $TICKSPERSEC;
    #get end date
    ($en_sec, $en_min, $en_hour, $en_mday, $en_mon, $en_year, $en_wday, $en_yday, $en_isdst) = localtime($ac_btime+$etime_real);
    $en_date = sprintf("%4d-%02d-%02d_%02d:%02d:%02d", $en_year+1900, $en_mon+1, $en_mday, $en_hour, $en_min, $en_sec);
    #get block io
    $bio = ($ac_rw & 8191) * (8 ** ($ac_rw >> 13));
    #get chr io
    $cio = ($ac_io & 8191) * (8 ** ($ac_io >> 13));
    #Get User CPU time
    $ucpu_tim = ($ac_utime & 8191) * (8 ** ($ac_utime >> 13)) / $TICKSPERSEC;
    #Get System CPU time
    $scpu_tim = ($ac_stime & 8191) * (8 ** ($ac_stime >> 13)) / $TICKSPERSEC;
    #Get RAM
    $ram = ($ac_mem & 8191) * (8 ** ($ac_mem >> 13));
    #Compute mean RAM use
    if(($ac_stime+$ac_utime) > 0)
      { $ram = $ram / ($ac_stime+$ac_utime); }
    $ram = $ram * $PAGESIZE;
    $flags = ($ac_flag & 01?"F":"_") . ($ac_flag & 02?"R":"_");

    #Print the record data out.
    printf("%-10s %-10s %-10s %20s %20s %12.2f %12.2f %12.2f %10d %12.2f %15.1f %5d %5s\n",
           $ac_comm, $ac_uname, $ac_grp, $st_date, $en_date, $etime_real, $ucpu_tim, $scpu_tim, $ram, $bio, $cio, int($ac_stat), $flags);
  }
}
close(FP);