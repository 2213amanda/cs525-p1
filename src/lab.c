#include "lab.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h>

int parseArgs(int argc, char **argv, char **from, char **to, char **subject, char **body, 
              char **port, char **helo_host, char **server){
    int opt;
    *from = NULL;
    *to = NULL;
    *subject = "";
    *body = NULL;
    *port = "25";
    *helo_host = "localhost";
    *server = NULL;

    while ((opt = getopt(argc, argv, ":f:t:s:b:p:H:")) != -1) {
        switch (opt) {
            case 'f':
                *from = optarg;
                break;

            case 't':
                *to = optarg;
                break;

            case 's':
                *subject = optarg;
                break;

            case 'b':
                *body = optarg;
                break;

            case 'p':
                *port = optarg;
                break;

            case 'H':
                *helo_host = optarg;
                break;

            case ':':
                fprintf(stderr, "Error: option -%c requires an argument\n",
                        optopt);
                return 1;

            case '?':
                fprintf(stderr, "Error: unknown option -%c\n", optopt);
                return 1;

            default:
                return 1;
        }
    }

    if (*from == NULL) {
        fprintf(stderr, "Error: -f <from> is required\n");
        return 1;
    }
    if (*to == NULL) {
        fprintf(stderr, "Error: -t <to> is required\n");
        return 1;
    }
    // if (*subject == NULL) {
    //     fprintf(stderr, "Error: -s <subject> is required\n");
    //     return 1;
    // } //FIXME causing problems circle back later

    
    if (optind >= argc) {
        fprintf(stderr, "Error: server is required\n");
        return 1;
    }

    *server = argv[optind];

    if (optind + 1 < argc) {
        fprintf(stderr, "Error: unexpected argument: %s\n",
                argv[optind + 1]);
        return 1;
    }

    return 0;
}


int resolveAddr(const char *server, const char *port, struct addrinfo **results) {

    struct addrinfo hints;
    int status;

    *results = NULL;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(server, port, &hints, results);

    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    return 0;
}

int serverConnect(struct addrinfo *results){

    struct addrinfo *current;
    int sockfd;

    for (current = results; current != NULL; current = current->ai_next) {

        sockfd = socket(current->ai_family, current->ai_socktype, current->ai_protocol);

        if (sockfd == -1) {
            continue;
        }

        if (connect(sockfd, current->ai_addr, current->ai_addrlen) == 0) {
            return sockfd;
        }

        close(sockfd);
    }

    fprintf(stderr, "Error: could not connect to server\n");

    return -1;
}

int getResponse(int sockfd, int expected_code){

    char buffer[1024];
    int position = 0;
    int code;
    char c;

    while (1) {
        position = 0;

        while (position < (int)sizeof(buffer) - 1) {
            ssize_t bytes_read = recv(sockfd, &c, 1, 0);

            if (bytes_read == 0) {
                fprintf(stderr, "Error: server closed connection\n");
                return 1;
            }

            if (bytes_read < 0) {
                perror("recv");
                return 1;
            }

            buffer[position++] = c;

            if (c == '\n') {
                break;
            }
        }

        buffer[position] = '\0';

        if (position < 3) {
            fprintf(stderr, "Error: invalid SMTP response\n");
            return 1;
        }

        if (buffer[0] < '0' || buffer[0] > '9' ||
            buffer[1] < '0' || buffer[1] > '9' ||
            buffer[2] < '0' || buffer[2] > '9') {

            fprintf(stderr, "Error: invalid SMTP response: %s", buffer);
            return 1;
        }

        code = (buffer[0] - '0') * 100 +
               (buffer[1] - '0') * 10 +
               (buffer[2] - '0');

        if (position >= 4 && buffer[3] == '-') {
            continue;
        }

        if (code != expected_code) {
            fprintf(stderr,
                    "Error: expected SMTP response %d, got %d\n", expected_code, code);
            return 1;
        }

        return 0;
    }
}


int sendCommand(int sockfd, const char *command){
    return 0;
}

int sendMessage(int sockfd, const char *from, const char *to, const char *subject, const char *body){
    return 0;
}
