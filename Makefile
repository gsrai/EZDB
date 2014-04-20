# EZDB make file

CC = gcc
TARGET = ezdb

all: $(TARGET)

$(TARGET): main.h main.c db.c
	$(CC) main.c db.c -o $(TARGET)

clean: 
	$(RM) $(TARGET)
