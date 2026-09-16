#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"
#include <getopt.h>
#include <netdb.h> 
#include <sys/socket.h>


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
  return UNITY_END();
}
