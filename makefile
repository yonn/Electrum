CC = g++
DEBUG = -g
D_CFLAGS = -Wall -Wextra -std=c++14 -c $(DEBUG)
D_LFLAGS = -Wall -Wextra -std=c++14 $(DEBUG)

debug_electrum: src/main.cpp $(OBJS)
	$(CC) $(D_LFLAGS) src/main.cpp $(OBJS) -o bin/electrum
