CC = gcc
CFLAGS = -ggdb3 -Wall -Werror -pedantic -std=gnu99

TARGET = test

SRCS = test.c
OBJS = test.o


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
