CC = gcc
CFLAGS = -ggdb3 -Wall -Werror -pedantic -std=gnu99

TARGET = breaker

SRCS = breaker.c
OBJS = breaker.o


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


breaker.o: breaker.c
	$(CC) $(CFLAGS) -c breaker.c -o breaker.o


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
