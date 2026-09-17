#include "lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>

#ifdef TEST
#define main main_exclude
#endif


int main(int argc, char **argv){

    char *from = NULL;
    char *to = NULL;
    char *subject = NULL;
    char *body = NULL;
    char *port = NULL;
    char *helo_host = NULL;
    char *server = NULL;

    struct addrinfo *results = NULL;
    int sockfd = -1;

    if (argc == 1) {
        printf("Usage: myapp -f <from> -t <to> [-s subject] [-b body] [-p port] [-H helo-host] <server>\n");
        printf("\n");
        printf("  -f <from>       envelope sender, for example you@example.com\n");
        printf("  -t <to>         envelope recipient\n");
        printf("  -s <subject>    subject line (default: empty)\n");
        printf("  -b <body>       message body (default: read from stdin)\n");
        printf("  -p <port>       port or service name (default: 25)\n");
        printf("  -H <helo-host>  host name sent with HELO (default: localhost)\n");
        printf("  <server>        host name or address of the mail server\n");
        return 0;
    }

    if (parseArgs(argc, argv, &from, &to, &subject, &body, &port, &helo_host, &server) != 0) {
        return 1;
    }


    if (resolveAddr(server, port, &results) != 0) {
        return 2;
    }

    sockfd = serverConnect(results);

    freeaddrinfo(results);
    results = NULL;

    if (sockfd < 0) {
        return 2;
    }

    if (getResponse(sockfd, 220) != 0) {
        close(sockfd);
        return 2;
    }

    //HELO
    {
        char command[1024];

        int written = snprintf(command,
                               sizeof(command),
                               "HELO %s",
                               helo_host);

        if (written < 0 || (size_t)written >= sizeof(command)) {
            fprintf(stderr, "Error: HELO command is too long\n");
            close(sockfd);
            return 2;
        }

        if (sendCommand(sockfd, command) != 0) {
            close(sockfd);
            return 2;
        }

        if (getResponse(sockfd, 250) != 0) {
            close(sockfd);
            return 2;
        }
    }

    // FROM
    {
        char command[1024];

        int written = snprintf(command,
                               sizeof(command),
                               "MAIL FROM:<%s>",
                               from);

        if (written < 0 || (size_t)written >= sizeof(command)) {
            fprintf(stderr, "Error: MAIL FROM command is too long\n");
            close(sockfd);
            return 2;
        }

        if (sendCommand(sockfd, command) != 0) {
            close(sockfd);
            return 2;
        }

        if (getResponse(sockfd, 250) != 0) {
            close(sockfd);
            return 2;
        }
    }

    // RCPT
    {
        char command[1024];

        int written = snprintf(command,
                               sizeof(command),
                               "RCPT TO:<%s>",
                               to);

        if (written < 0 || (size_t)written >= sizeof(command)) {
            fprintf(stderr, "Error: RCPT TO command is too long\n");
            close(sockfd);
            return 2;
        }

        if (sendCommand(sockfd, command) != 0) {
            close(sockfd);
            return 2;
        }

        if (getResponse(sockfd, 250) != 0) {
            close(sockfd);
            return 2;
        }
    }

    // DATA
    if (sendCommand(sockfd, "DATA") != 0) {
        close(sockfd);
        return 2;
    }

    if (getResponse(sockfd, 354) != 0) {
        close(sockfd);
        return 2;
    }


    if (sendMessage(sockfd, from, to, subject, body) != 0) {
        close(sockfd);
        return 2;
    }

    if (getResponse(sockfd, 250) != 0) {
        close(sockfd);
        return 2;
    }

    // QUIT
    if (sendCommand(sockfd, "QUIT") != 0) {
        close(sockfd);
        return 2;
    }

    if (getResponse(sockfd, 221) != 0) {
        close(sockfd);
        return 2;
    }

    close(sockfd);

    return 0;

}