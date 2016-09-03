CC = g++
DEBUG = -g
D_CFLAGS = -Wall -Wextra -std=c++14 -c $(DEBUG)
D_LFLAGS = -Wall -Wextra -std=c++14 $(DEBUG)

OBJS = bin/electrum.o bin/lexer.o bin/read.o bin/error.o

debug_electrum: src/main.cpp $(OBJS)
	$(CC) $(D_LFLAGS) src/main.cpp $(OBJS) -o bin/electrum

bin/electrum.o: src/electrum.cpp src/electrum.hpp src/read.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/electrum.cpp -o bin/electrum.o

bin/read.o: src/read.cpp src/read.hpp src/lexer.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/read.cpp -o bin/read.o

bin/lexer.o: src/lexer.cpp src/lexer.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/lexer.cpp -o bin/lexer.o

bin/error.o: src/error.cpp src/error.hpp
	$(CC) $(D_CFLAGS) src/error.cpp -o bin/error.o
