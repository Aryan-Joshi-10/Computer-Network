// udp_server.cpp
#include <iostream>
#include <cstring>
// #include <sys/socket.h>
// #include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Zero out structure
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Server info
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    cout << "UDP Server listening on port " << PORT << "...\n";

    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
    buffer[n] = '\0';
    cout << "Client: " << buffer << endl;

    const char* response = "Hello from server!";
    sendto(sockfd, response, strlen(response), 0, (const struct sockaddr*)&client_addr, client_len);

    close(sockfd);
    return 0;
}
