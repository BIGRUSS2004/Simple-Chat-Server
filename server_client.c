#include "server.h"
#include <ctype.h>

#define DELIMITERS " \t\n" // Define delimiters for strtok

void *client_receive(void *ptr) {
    int client = *(int *)ptr;
    char buffer[MAXBUFF], cmd[MAXBUFF], username[20];
    char *arguments[80];
    int received;

    sprintf(username, "guest%d", client); // Assign a default username

    pthread_mutex_lock(&rw_lock);
    head = insertFirstU(head, client, username); // Add user to the user list
    addUserToRoom(roomList, "Lobby", username); // Add user to default room
    pthread_mutex_unlock(&rw_lock);

    send(client, server_MOTD, strlen(server_MOTD), 0);

    while ((received = READ(client, buffer, MAXBUFF)) > 0) {
        buffer[received] = '\0';
        strcpy(cmd, buffer);

        arguments[0] = strtok(cmd, DELIMITERS);
        int i = 0;
        while (arguments[i] != NULL) {
            arguments[++i] = strtok(NULL, DELIMITERS);
        }

        if (arguments[0] != NULL) {
            if (strcmp(arguments[0], "say") == 0 && i > 1) { // Handle "say" command
                char message[MAXBUFF] = {0};
                snprintf(message, MAXBUFF, "%s: %s\n", username, buffer + 4); // Skip "say "

                pthread_mutex_lock(&rw_lock);
                struct node *current = head;
                while (current != NULL) { // Broadcast to all users
                    send(current->socket, message, strlen(message), 0);
                    current = current->next;
                }
                pthread_mutex_unlock(&rw_lock);
            } else {
                send(client, "Unknown command\n", 17, 0);
            }
        }
    }

    // Remove user on disconnect
    pthread_mutex_lock(&rw_lock);
    removeUserFromAllRooms(roomList, username);
    head = removeUser(head, username);
    pthread_mutex_unlock(&rw_lock);

    CLOSE_SOCKET(client);
    return NULL;
}
