# 编译器及编译标志
CC = gcc
CFLAGS = -ggdb3 -Wall -Werror -pedantic -std=gnu99

# 目标可执行文件名
TARGET = test-power

# 源文件和对象文件
SRCS = power.c test-power.c
OBJS = power.o test-power.o

# 生成目标可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 生成对象文件

power.o: power.c
	$(CC) $(CFLAGS) -c power.c -o power.o

test-power.o: test-power.c
	$(CC) $(CFLAGS) -c test-power.c -o test-power.o

# 清理生成的中间文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
