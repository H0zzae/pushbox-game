all:header

header:pushbox.o
	g++ -W -Wall -o header pushbox.o -lncurses

pushbox.o:pushbox.cpp
	g++ -W -Wall -c -o pushbox.o pushbox.cpp -lncurses
