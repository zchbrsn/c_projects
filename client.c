#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

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
        }

        // Receive data from server
        char response[256];
        int recvlen = recv(client_sock, response, sizeof(response) -1, 0);

        if (recvlen < 0) {
            printf("[-] Failed to receive data from server: %s\n", strerror(errno));
        }
        else {
            printf("[+] Received response from server: %s\n", response);
        }

        // Close socket
        if (close(client_sock) != 0) {
            printf("[-] Failed to close socket: %s\n", strerror(errno));
            exit(1);
        }
        return 0;
    }
}