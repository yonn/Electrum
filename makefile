CC = g++
DEBUG = -g
D_CFLAGS = -Wall -Wextra -std=c++14 -c $(DEBUG)
D_LFLAGS = -Wall -Wextra -std=c++14 $(DEBUG)

OBJS = bin/electrum.o \
       bin/builtins.o \
       bin/eval.o     \
       bin/read.o     \
       bin/object.o   \
       bin/lexer.o    \
       bin/error.o

OBJ_CLASSES = src/objects/*.hpp

electrum: src/main.cpp $(OBJS)
	$(CC) $(D_LFLAGS) src/main.cpp $(OBJS) -o bin/electrum

bin/electrum.o: src/electrum.cpp src/electrum.hpp src/read.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/electrum.cpp -o bin/electrum.o

bin/builtins.o: src/builtins.cpp src/builtins.hpp src/eval.hpp src/object.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/builtins.cpp -o bin/builtins.o

bin/eval.o: src/eval.cpp src/eval.hpp src/object.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/eval.cpp -o bin/eval.o

bin/read.o: src/read.cpp src/read.hpp src/object.hpp src/lexer.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/read.cpp -o bin/read.o

bin/object.o: src/object.cpp src/object.hpp $(OBJ_CLASSES)
	$(CC) $(D_CFLAGS) src/object.cpp -o bin/object.o

bin/lexer.o: src/lexer.cpp src/lexer.hpp src/error.hpp
	$(CC) $(D_CFLAGS) src/lexer.cpp -o bin/lexer.o

bin/error.o: src/error.cpp src/error.hpp
	$(CC) $(D_CFLAGS) src/error.cpp -Wno-varargs -o bin/error.o
