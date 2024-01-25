#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
Arguments:
    protocol (tcp/udp)
    IP or IP range to scan
    port or port range to scan
Example:
    port_scanner tcp 127.0.0.1 127.0.0.1 1 65535
*/

int main(int argc, char *argv[]) {

    if (argc < 5 || argc > 6) {
        // Usage statement
        printf("Usage:\t%s <tcp|udp> <IP Address> <Port Start> <Port End> [-b]\n", argv[0]);
        printf("\t -b is used to collect banner information.\n");
        printf("Examples:\n\t%s tcp 127.0.0.1 22 22\n", argv[0]);
        printf("\t%s udp 192.168.0.1 1 1024\n", argv[0]);
        exit(1);
    }

    // Ambiguous Variables for both protocol options
    in_addr_t ip_addr = inet_addr(argv[2]);
    int start_port = atoi(argv[3]);
    int end_port = atoi(argv[4]);
    int sock;
    // end ambiguous variables

    // Build timeout structure
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    // TCP scanner
    if (strcmp("tcp", argv[1]) == 0) {

        printf("[+] Trying ports = %d-%d\n", start_port, end_port);
        for (int port = start_port; port <= end_port; port++) {

            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0) {
                printf("[-] Socket Creation Error: %s", strerror(errno));
                exit(1);
            }
            if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) < 0) {
                printf("[-] Socket option error: %s\n", strerror(errno));
                exit(1);
            }
            /*
            // Setting the port to non-blocking doesn't seem to return any responses or determine if a port is closed or open
            // where socketfd is the socket you want to make non-blocking
            int status = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);
            if (status < 0){
                printf("[-] Cannot set socket to non-blocking: %s\n", strerror(errno));
            }
            */

            struct sockaddr_in conn_addr;
            conn_addr.sin_family = AF_INET;
            conn_addr.sin_port = htons(port);
            conn_addr.sin_addr.s_addr = ip_addr;

            int res = connect(sock, (struct sockaddr *)&conn_addr, sizeof(conn_addr));
            if (res < 0) {
                if (argc == 6 && strcmp(argv[5], "-b") == 0) {
                    char response[256];
                    int recvlen = recv(sock, response, sizeof(response) -1, 0);
                    if (recvlen < 0) {
                        if (errno == EWOULDBLOCK || errno == ETIMEDOUT) {
                            printf("[-] Timeout receiving data on port %d\n", port);
                            close(sock);
                        }
                        else {
                            printf("[-] Failed to receive data from server: %s\n", strerror(errno));
                        }
                    }
                    else {
                        response[recvlen] = '\0';
                        printf("Received %d bytes from server\n", recvlen); // Debug print
                        printf("%s\n", response);
                    }
                }
            }
            else {
                printf("[+] Port %d open.\n", port);
            }
            close(sock);
        }
        exit(0);
    }
    // UDP Scanner
    else if (strcmp("udp", argv[1]) == 0) {

        // Loop through ports from start - end
        printf("[+] Trying ports = %d-%d\n", start_port, end_port);
        for (int port = start_port; port <= end_port; port++) {

            sock = socket(AF_INET, SOCK_DGRAM, 0);
            if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) < 0) {
                printf("[-] Socket option error: %s\n", strerror(errno));
                exit(1);
            }
            if (sock < 0) {
                printf("[-] Socket Creation Error: %s", strerror(errno));
                exit(1);
            }
            /*
            // Setting the port to non-blocking doesn't seem to return any responses or determine if a port is closed or open
            // where socketfd is the socket you want to make non-blocking
            int status = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);
            if (status < 0){
                printf("[-] Cannot set socket to non-blocking: %s\n", strerror(errno));
            }
            */
        
        // Build UDP socket structure
        struct sockaddr_in conn_addr;
        conn_addr.sin_family = AF_INET;
        conn_addr.sin_port = htons(port);
        conn_addr.sin_addr.s_addr = ip_addr;

        // Need to send a UDP packet and accept a response from the server
        // Send UDP Packet
        char sendbuf[1] = "";
        if (sendto(sock, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *) &conn_addr, sizeof(conn_addr)) < 0) {
            printf("[-] Error sending packet: %s", strerror(errno));
            exit(1);
        }

        // If receiving a response, assume UDP port is open, else timeout
        char recvbuf[1024];
        int recvlen = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
        if (recvlen < 0) {
            if (errno == EWOULDBLOCK) {
                printf("[-] Timeout on port %d\n", port);
            }
            else {
                printf("[-] Error receiving packet: %s\n", strerror(errno));
            }
        }
        else {
            printf("[+] Port %d open\n", port);
        }

        close(sock);
        }
        exit(0);
    }

    // Invalid protocol
    else {
        printf("[-] Did not provide a correct protocol (e.g., tcp/udp)\n");
        exit(1);
    }

}