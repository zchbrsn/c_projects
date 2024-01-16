#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // Check args
    if (argc != 3) {
        printf("Usage: %s <Bind IP> <Bind Port>\n", argv[0]);
        exit(1);
    }

    char server_message[256] = "Hello, welcome to my server.\n";

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
        }

        int client_sock = accept(server_sock, NULL, NULL);
        // Send message
        if (client_sock < 0) {
            printf("[-] Accept error: %s/n", strerror(errno));
        }
        else {
            send(client_sock, server_message, sizeof(server_message), 0);
        }
    }

    if (close(server_sock) != 0) {
        printf("[-] Failed to close socket: %s\n", strerror(errno));
        exit(1);
    }

    return 0;
}