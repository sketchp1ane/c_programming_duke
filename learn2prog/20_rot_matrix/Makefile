# 编译器及编译标志
CC = gcc
CFLAGS = -ggdb3 -Wall -Werror -pedantic -std=gnu99

# 目标可执行文件名
TARGET = rotate-matrix

# 源文件和对象文件
SRCS = rotate.c
OBJS = read-matrix.o rotate.o

# 生成目标可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 生成对象文件

rotate.o: rotate.c
	$(CC) $(CFLAGS) -c rotate.c -o rotate.o

# 清理生成的中间文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
