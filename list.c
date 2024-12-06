#include "list.h"

/* USER FUNCTIONS */

// Insert a user at the beginning of the list
struct node* insertFirstU(struct node *head, int socket, char *username) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->username, username);
    newNode->socket = socket;
    newNode->next = head;
    return newNode;
}

// Find a user by username
struct node* findU(struct node *head, char *username) {
    struct node *current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Remove a user from the list by username
struct node* removeUser(struct node *head, char *username) {
    struct node *current = head;
    struct node *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
    }
    return head;
}

// List all users in a room
void listUsers(struct node *head, char *output) {
    struct node *current = head;
    while (current != NULL) {
        strcat(output, current->username);
        strcat(output, "\n");
        current = current->next;
    }
}

/* ROOM FUNCTIONS */

// Create a room
struct room* createRoom(const char *roomName) { // Updated to use const char *
    struct room *newRoom = (struct room *)malloc(sizeof(struct room));
    strcpy(newRoom->roomName, roomName);
    newRoom->userList = NULL;
    newRoom->next = NULL;
    return newRoom;
}

// Find a room by name
struct room* findRoom(struct room *head, char *roomName) {
    struct room *current = head;
    while (current != NULL) {
        if (strcmp(current->roomName, roomName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Add a user to a room
bool addUserToRoom(struct room *roomList, char *roomName, char *username) {
    struct room *room = findRoom(roomList, roomName);
    if (room == NULL) {
        return false;
    }
    room->userList = insertFirstU(room->userList, -1, username);
    return true;
}

// Remove a user from a room
bool removeUserFromRoom(struct room *roomList, char *roomName, char *username) {
    struct room *room = findRoom(roomList, roomName);
    if (room == NULL) {
        return false;
    }
    room->userList = removeUser(room->userList, username);
    return true;
}

// List all rooms
void listRooms(struct room *roomList, char *output) {
    struct room *current = roomList;
    while (current != NULL) {
        strcat(output, current->roomName);
        strcat(output, "\n");
        current = current->next;
    }
}

// Update username in all rooms
void updateUserInRooms(struct room *roomList, char *oldUsername, char *newUsername) {
    struct room *currentRoom = roomList;
    while (currentRoom != NULL) {
        struct node *currentUser = currentRoom->userList;
        while (currentUser != NULL) {
            if (strcmp(currentUser->username, oldUsername) == 0) {
                strcpy(currentUser->username, newUsername);
            }
            currentUser = currentUser->next;
        }
        currentRoom = currentRoom->next;
    }
}

// Remove user from all rooms
void removeUserFromAllRooms(struct room *roomList, char *username) {
    struct room *currentRoom = roomList;
    while (currentRoom != NULL) {
        currentRoom->userList = removeUser(currentRoom->userList, username);
        currentRoom = currentRoom->next;
    }
}
