CC=gcc
CFLAGS=-g -Wall
TARGET=exe.out
OBJS=GraphTypeMat.o GraphTypeList.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

GraphTypeMat.o : GraphTypeMat.c GraphTypeMat.h
	$(CC) -c -o GraphTypeMat.o GraphTypeMat.c

GraphTypeList.o : GraphTypeList.c GraphTypeList.h
	$(CC) -c -o GraphTypeList.o GraphTypeList.c

main.o : main.c
	$(CC) -c -o main.o main.c

clean:
	rm $(OBJECT) $(TARGET)