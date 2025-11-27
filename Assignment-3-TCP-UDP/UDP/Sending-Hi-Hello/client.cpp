// udp_client.cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Zero out structure
    memset(&server_addr, 0, sizeof(server_addr));

    // Server info
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    const char* msg = "Hello from client!";
    sendto(sockfd, msg, strlen(msg), 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    buffer[n] = '\0';
    cout << "Server: " << buffer << endl;

    close(sockfd);
    return 0;
}
