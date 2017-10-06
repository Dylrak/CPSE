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
SOURCES := melody.cpp base_player.cpp

# header files in this project
HEADERS := melody.hpp note.hpp player.hpp base_player.hpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due

# make the song file with a string
melody.cpp: Makefile make_melody.exe
	make_melody "DJ Jean - The Launch : d=4,o=5,b=140:8p,8b,8p,8b,8p,8a#,8p,8a#,8p,8a,8p,8a,8p,8a,8p,8e,8p,8a,8p,8a,8p,8a,8p,8e,8p,8g,8p,8g,8p,8g,8p,8e," > melody.cpp

make_melody.exe: make_melody.cpp base_player.cpp
	g++ make_melody.cpp base_player.cpp -o make_melody.exe -std=c++11