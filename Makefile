CC = gcc
CFLAGS = -Wall -pthread
SRCS = server.c server_client.c list.c
TARGET = server

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
