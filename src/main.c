#include <sys/socket.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netinet/in.h>

void main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        AF_INET,
        0x901f,
        0
    };

    bind(s, &addr, sizeof(addr));

    listen(s, 10);

    int client_fd = accept(s, 0, 0);

    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    char* f = buffer + 5;
    *strchr(f, ' ') = 0;
    // int opened_fd = open(f, O_RDONLY);
    // sendfile(client_fd, 256, 0, 256, opened_fd, 0);
    // close(opened_fd);
    close(client_fd);
    close(s);
}