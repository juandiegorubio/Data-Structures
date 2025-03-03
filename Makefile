CC = g++
CFLAGS = -Wall -Wextra

btree: btree.cpp
	$(CC) $(CFLAGS) -o btree btree.cpp

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp

