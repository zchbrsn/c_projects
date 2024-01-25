#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

    /*  Code here to to remember how to stop system signals
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGKILL);
    sigaddset(&sigset, SIGSTOP);
    sigaddset(&sigset, SIGTERM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    */

    if (argc != 3) {
        printf("Usage: %s <IP Address> <Port>\n", argv[0]);
        exit(1);
    }
    else {
        
        // User specified IP and Port to bind
        char *ip = argv[1];
        int port = atoi(argv[2]);

        // Create socket
        int client_sock = socket(AF_INET, SOCK_STREAM, 0);

        // Build socket structure
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr(ip);    // INADDR_ANY = 0.0.0.0
        server_address.sin_port = htons(port);

        // Error handling for no connection
        if (connect(client_sock, (struct sockaddr *)&server_address, sizeof(server_address)) != 0) {
            printf("[-] Failed to connect to remote server %s: %s\n", ip, strerror(errno));
            close(client_sock);
            exit(1);
        }

        // Receive data from server
        char response[256];
        char command[256];

        puts("[+] Connected");
        while (1) {
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = 0;
            send(client_sock, command, strlen(command), 0);
            int recvlen = recv(client_sock, response, sizeof(response) -1, 0);
            printf("Received %d bytes from server\n", recvlen); // Debug print
            if (recvlen < 0) {
                printf("[-] Failed to receive data from server: %s\n", strerror(errno));
            }
            else {
                response[recvlen] = '\0';
                printf("%s\n", response);
            }

            if (strcmp(command, "exit") == 0) {
                // Close socket
                close(client_sock);
                exit(0);
            }
        }
        return 0;
    }
}