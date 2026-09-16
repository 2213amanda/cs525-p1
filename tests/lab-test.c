#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"
#include <getopt.h>
#include <netdb.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


void setUp(void) {
  printf("Setting up tests...\n");
  optind = 1;
}

void tearDown(void) {
  printf("Tearing down tests...\n");
}

//parse args tests

void test_parseArgs_required_arguments(void){

    char *argv[] = {
        "myapp",
        "-f", "alice@example.com",
        "-t", "bob@example.com",
        "mail.example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_EQUAL_INT(0, result);

    TEST_ASSERT_EQUAL_STRING("alice@example.com", from);
    TEST_ASSERT_EQUAL_STRING("bob@example.com", to);
    TEST_ASSERT_EQUAL_STRING("", subject);
    TEST_ASSERT_NULL(body);
    TEST_ASSERT_EQUAL_STRING("25", port);
    TEST_ASSERT_EQUAL_STRING("localhost", helo_host);
    TEST_ASSERT_EQUAL_STRING("mail.example.com", server);
}


void test_parseArgs_all_arguments(void){

    char *argv[] = {
        "myapp",
        "-f", "alice@example.com",
        "-t", "bob@example.com",
        "-s", "Test Subject",
        "-b", "Hello Bob!",
        "-p", "587",
        "-H", "mycomputer",
        "mail.example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_EQUAL_INT(0, result);

    TEST_ASSERT_EQUAL_STRING("alice@example.com", from);
    TEST_ASSERT_EQUAL_STRING("bob@example.com", to);
    TEST_ASSERT_EQUAL_STRING("Test Subject", subject);
    TEST_ASSERT_EQUAL_STRING("Hello Bob!", body);
    TEST_ASSERT_EQUAL_STRING("587", port);
    TEST_ASSERT_EQUAL_STRING("mycomputer", helo_host);
    TEST_ASSERT_EQUAL_STRING("mail.example.com", server);
}



void test_parseArgs_missing_from(void){

    char *argv[] = {
        "myapp",
        "-t", "bob@example.com",
        "mail.example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_NOT_EQUAL(0, result);
}


void test_parseArgs_missing_to(void){

    char *argv[] = {
        "myapp",
        "-f", "alice@example.com",
        "mail.example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_NOT_EQUAL(0, result);
}


void test_parseArgs_missing_server(void){

    char *argv[] = {
        "myapp",
        "-f", "alice@example.com",
        "-t", "bob@example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_NOT_EQUAL(0, result);
}


void test_parseArgs_unknown_option(void){

    char *argv[] = {
        "myapp",
        "-x", "something",
        "-f", "alice@example.com",
        "-t", "bob@example.com",
        "mail.example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_NOT_EQUAL(0, result);
}

void test_parseArgs_missing_option_argument(void){

    char *argv[] = {
        "myapp",
        "-f",
        "-t", "bob@example.com",
        "mail.example.com"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_NOT_EQUAL(0, result);
}

void test_parseArgs_extra_argument(void){

    char *argv[] = {
        "myapp",
        "-f", "alice@example.com",
        "-t", "bob@example.com",
        "mail.example.com",
        "extra"
    };

    int argc = sizeof(argv) / sizeof(argv[0]);

    char *from;
    char *to;
    char *subject;
    char *body;
    char *port;
    char *helo_host;
    char *server;

    int result = parseArgs(argc, argv, &from, &to, &subject, &body,
                           &port, &helo_host, &server);

    TEST_ASSERT_NOT_EQUAL(0, result);
}

//resolveAddr tests

void test_resolveAddr_localhost(void){

    struct addrinfo *results = NULL;

    int result = resolveAddr("localhost", "25", &results);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(results);

    TEST_ASSERT_EQUAL_INT(SOCK_STREAM, results->ai_socktype);

    freeaddrinfo(results);
}


void test_resolveAddr_ipv4_loopback(void){

    struct addrinfo *results = NULL;

    int result = resolveAddr("127.0.0.1", "25", &results);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(results);

    TEST_ASSERT_EQUAL_INT(SOCK_STREAM, results->ai_socktype);

    freeaddrinfo(results);
}


void test_resolveAddr_invalid_server(void){

    struct addrinfo *results = NULL;

    int result = resolveAddr(
        "definitely.a.real.server", "25", &results);

    TEST_ASSERT_NOT_EQUAL(0, result);

    TEST_ASSERT_NULL(results);
}


void test_resolveAddr_invalid_port(void){

    struct addrinfo *results = NULL;

    int result = resolveAddr("localhost", "not-a-valid-port", &results);

    TEST_ASSERT_NOT_EQUAL(0, result);

    TEST_ASSERT_NULL(results);
}


void test_resolveAddr_empty_server(void){
  
    struct addrinfo *results = NULL;

    int result = resolveAddr("", "25", &results);

    TEST_ASSERT_NOT_EQUAL(0, result);

    TEST_ASSERT_NULL(results);
}


// serverConnect tests

void test_serverConnect_localhost(void){

    int listenfd;
    int sockfd;
    int clientfd;

    struct sockaddr_in server_addr;
    socklen_t addr_len;

    struct addrinfo *results = NULL;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    TEST_ASSERT_NOT_EQUAL(-1, listenfd);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    server_addr.sin_port = htons(0);

    TEST_ASSERT_EQUAL_INT(0, bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)));

    addr_len = sizeof(server_addr);

    TEST_ASSERT_EQUAL_INT(0, getsockname(listenfd, (struct sockaddr *)&server_addr, &addr_len));

    TEST_ASSERT_EQUAL_INT(0, listen(listenfd, 1));

    char port[16];

    snprintf(port, sizeof(port), "%u", ntohs(server_addr.sin_port));

    TEST_ASSERT_EQUAL_INT(0, resolveAddr("127.0.0.1", port, &results));

    TEST_ASSERT_NOT_NULL(results);

    sockfd = serverConnect(results);

    TEST_ASSERT_NOT_EQUAL(-1, sockfd);

    clientfd = accept(listenfd, NULL, NULL);

    TEST_ASSERT_NOT_EQUAL(-1, clientfd);

    close(clientfd);
    close(sockfd);
    close(listenfd);

    freeaddrinfo(results);
}


void test_serverConnect_no_server(void){

    struct addrinfo *results = NULL;

    TEST_ASSERT_EQUAL_INT(0, resolveAddr("127.0.0.1", "1", &results));

    TEST_ASSERT_NOT_NULL(results);

    int sockfd = serverConnect(results);

    TEST_ASSERT_EQUAL_INT(-1, sockfd);

    freeaddrinfo(results);
}

void test_serverConnect_null_results(void){

    int sockfd = serverConnect(NULL);

    TEST_ASSERT_EQUAL_INT(-1, sockfd);
}


//getResponse tests

void test_getResponse_correct_code(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    const char *response =
        "220 mail.example.com ESMTP\r\n";

    ssize_t bytes_sent = send(
        sockets[0],
        response,
        strlen(response),
        0
    );

    TEST_ASSERT_EQUAL_INT(strlen(response), bytes_sent);

    int result = getResponse(sockets[1], 220);

    TEST_ASSERT_EQUAL_INT(0, result);

    close(sockets[0]);
    close(sockets[1]);
}

void test_getResponse_wrong_code(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    const char *response =
        "550 Mailbox unavailable\r\n";

    ssize_t bytes_sent = send(
        sockets[0],
        response,
        strlen(response),
        0
    );

    TEST_ASSERT_EQUAL_INT(strlen(response), bytes_sent);

    int result = getResponse(sockets[1], 220);

    TEST_ASSERT_NOT_EQUAL(0, result);

    close(sockets[0]);
    close(sockets[1]);
}


void test_getResponse_multiline(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    const char *response =
        "250-mail.example.com\r\n"
        "250-SIZE 10000000\r\n"
        "250-8BITMIME\r\n"
        "250 OK\r\n";

    ssize_t bytes_sent = send(
        sockets[0],
        response,
        strlen(response),
        0
    );

    TEST_ASSERT_EQUAL_INT(strlen(response), bytes_sent);

    int result = getResponse(sockets[1], 250);

    TEST_ASSERT_EQUAL_INT(0, result);

    close(sockets[0]);
    close(sockets[1]);
}


void test_getResponse_invalid_response(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    const char *response =
        "ABC Invalid response\r\n";

    ssize_t bytes_sent = send(
        sockets[0],
        response,
        strlen(response),
        0
    );

    TEST_ASSERT_EQUAL_INT(strlen(response), bytes_sent);

    int result = getResponse(sockets[1], 220);

    TEST_ASSERT_NOT_EQUAL(0, result);

    close(sockets[0]);
    close(sockets[1]);
}


void test_getResponse_connection_closed(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    close(sockets[0]);

    int result = getResponse(sockets[1], 220);

    TEST_ASSERT_NOT_EQUAL(0, result);

    close(sockets[1]);
}


void test_getResponse_short_response(void){
    
    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    const char *response =
        "22\r\n";

    ssize_t bytes_sent = send(
        sockets[0],
        response,
        strlen(response),
        0
    );

    TEST_ASSERT_EQUAL_INT(strlen(response), bytes_sent);

    int result = getResponse(sockets[1], 220);

    TEST_ASSERT_NOT_EQUAL(0, result);

    close(sockets[0]);
    close(sockets[1]);
}




int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_parseArgs_required_arguments);
  RUN_TEST(test_parseArgs_all_arguments);
  RUN_TEST(test_parseArgs_missing_from);
  RUN_TEST(test_parseArgs_missing_to);
  RUN_TEST(test_parseArgs_missing_server);
  RUN_TEST(test_parseArgs_unknown_option);
  RUN_TEST(test_parseArgs_missing_option_argument);
  RUN_TEST(test_parseArgs_extra_argument);
  RUN_TEST(test_resolveAddr_localhost);
  RUN_TEST(test_resolveAddr_ipv4_loopback);
  RUN_TEST(test_resolveAddr_invalid_server);
  RUN_TEST(test_resolveAddr_invalid_port);
  RUN_TEST(test_resolveAddr_empty_server);
  RUN_TEST(test_serverConnect_localhost);
  RUN_TEST(test_serverConnect_no_server);
  RUN_TEST(test_serverConnect_null_results);
  RUN_TEST(test_getResponse_correct_code);
  RUN_TEST(test_getResponse_wrong_code);
  RUN_TEST(test_getResponse_multiline);
  RUN_TEST(test_getResponse_invalid_response);
  RUN_TEST(test_getResponse_connection_closed);
  RUN_TEST(test_getResponse_short_response);
  return UNITY_END();
}
