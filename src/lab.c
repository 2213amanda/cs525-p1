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

int serverConnect(struct addrinfo *results)
{
    return 0;
}

int getResponse(int sockfd, int expected_code)
{
    return 0;
}

int sendCommand(int sockfd, const char *command)
{
    return 0;
}

int sendMessage(int sockfd, const char *from, const char *to, const char *subject, const char *body)
{
    return 0;
}
