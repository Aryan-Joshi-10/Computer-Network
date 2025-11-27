#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    string msg;
    cout << "Enter expression (sin/cos/tan <angle in degrees>): ";
    getline(std::cin, msg);

    sendto(sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    socklen_t len = sizeof(servaddr);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    cout << "Server: " << buffer << endl;

    close(sockfd);
    return 0;
}
