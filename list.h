#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* User Node Structure */
struct node {
   char username[30];
   int socket;
   struct node *next;
};

/* Room Structure */
struct room {
   char roomName[50];
   struct node *userList;
   struct room *next;
};

/* User Linked List Functions */
struct node* insertFirstU(struct node *head, int socket, char *username);
struct node* findU(struct node *head, char *username);
struct node* removeUser(struct node *head, char *username);
void listUsers(struct node *head, char *output);

/* Room Linked List Functions */
struct room* createRoom(const char *roomName);
struct room* findRoom(struct room *head, char *roomName);
bool addUserToRoom(struct room *roomList, char *roomName, char *username);
bool removeUserFromRoom(struct room *roomList, char *roomName, char *username);
void listRooms(struct room *roomList, char *output);
void updateUserInRooms(struct room *roomList, char *oldUsername, char *newUsername);
void removeUserFromAllRooms(struct room *roomList, char *username);

#endif
