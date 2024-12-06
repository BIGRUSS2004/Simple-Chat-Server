#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "list.h"

/* Platform-specific headers */
#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #define CLOSE_SOCKET closesocket
    #define SOCKET_ERROR_CHECK SOCKET_ERROR
    #define READ recv
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <netdb.h>
    #define CLOSE_SOCKET close
    #define SOCKET_ERROR_CHECK -1
    #define READ read
#endif

/* Constants */
#define MAX_READERS 25
#define PORT 8888
#define MAXBUFF 2096
#define BACKLOG 10

/* Global Variables */
extern pthread_mutex_t mutex;
extern pthread_mutex_t rw_lock;
extern struct node *head;
extern struct room *roomList;
extern const char *server_MOTD;

/* Function Prototypes */
int get_server_socket();
int start_server(int serv_socket, int backlog);
int accept_client(int serv_sock);
void sigintHandler(int sig_num);
void *client_receive(void *ptr);

#endif
