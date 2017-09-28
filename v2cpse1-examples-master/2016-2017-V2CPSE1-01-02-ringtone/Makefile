#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := melody.cpp song.cpp

# header files in this project
HEADERS := melody.hpp song.hpp note.hpp player.hpp

# other places to look for files for this project
SEARCH  :=
# make the song file with a string
melody.cpp: Makefile make_melody.exe
	make_melody "James Bond Theme : d=4,o=5,b=140:8e,16f#,16f#,8f#,f#,8e,8e,8e,8e,16g,16g,8g,g,8f#,8f#,8f#,8e,16f#,16f#,8f#,f#,8e,8e,8e,8e,16g,16g,8g,g,8f#,8f,8e,8d#6,2d.6,8b,8a,1b," > melody.cpp

make_melody.exe: make_melody.cpp
	g++ make_melody.cpp -o make_melody.exe
# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
