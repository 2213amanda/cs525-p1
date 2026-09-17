# Submission Report

- Submission generated at 09/17/2026 at 23:04:16

- Machine info: Linux runnervmlun5p 6.17.0-1022-azure #22-Ubuntu SMP Mon Jul 27 17:24:03 UTC 2026 x86_64 x86_64 x86_64 GNU/Linux

## Note to Students

Please read this report carefully before submission.
Ensure that all sections are complete and accurate.
Look for any errors in the build or test outputs.
If you find any issues, correct them before submitting.
Post any questions on the class discussion board for help.


---

## README

# Project 1

- Name: Amanda Tuttle
- Email: amandatuttle631@u.boisestate.edu
- Class: CS525

## Known Bugs or Issues

The only issue I know of is that the program does not currently use stdin to get the body of the message, but -b "message here" works in all tests.

## Experience

When I started this project, I spent quite a bit of time reading over the assignment and SMTP documentation, and while I understood the protocol and the end goal of what I was supposed to implement I did struggle quite a bit with turning the idea into structured C code. I would honestly say this was the hardest part of the project for me, though it was not the only difficulty I encountered along the way.

An error that was very difficult to figure out for me was that even though I had included <netdb.h> to be able to use addrinfo and getaddrinfo(), vscode was angrily underlining addrinfo in my lab.h declarations, but then if I erased struct and rewrote it the underline would go away. Then when I wrote getaddrinfo() in lab.c it was also not able to find the declaration. It turns out that some Linux systems control which declarations are visible from system headers and I had to manually expose the version of POSIX containing these definitions (and here I was using Linux because it was supposed to have the least problems!). 

I also had an issue when I was first starting writing tests, where the first test for parseArgs was running perfectly, the next test was failing, and some number of tests later was causing a very angry dramatic segmentation fault. I decided to figure out why the test was simply failing first because in that moment I wanted the seg fault to be a problem for later me, and after putting a debug point on just about every line of parseArgs I found out that optind wasn't being reset to 0 between tests and all I had to do was add one single line to lab-test setUp saying optind = 0 and it magically fixed all of my problems. 

While I was working towards 100% code coverage, I discovered that one of my test was failing successfully, but for the wrong reason. test_parseArgs_missing_from was set up so that -f had no argument and -t did, but it was simply interpreting -t as the argument for -f and failing because *to == NULL, and wasn't hitting the branch where -f had no argument. I fixed this by adding a test that only contained myapp -f as the input which successfully hit the branch.

Not an actual issue, but for the amusement of who reads this, I had commented out the first few RUN_TEST functions to make debugging easier while I was working on code coverage, but forgot to uncomment those lines before running make report again, and was deeply confused as to how I'd managed to make the coverage go *down*.

Overall, even though I did face quite a few struggles during this project, I did enjoy the debugging process and feel like I ended up with a good project.

## Design
While my functions are not strictly separated into three layers, the functionality within them is. All of the unit tests run locally without touching a live mail server by creating local socket pairs.

Protocol helpers: 
- parseArgs parses the command line input and checks its validity. In the case of the unit tests, a char array is passed into the function and parsed. 
- sendMessage builds the message to be sent after DATA is acknowledged and dot stuffs the body. In the unit tests, the message is sent using one local socket and received using the another.
- getResponse parses the reply line and decides whether a reply line is the final one. This is done in the unit tests by sending a char array from one local socket and getting the response with the other. 

The session: 
- getResponse reads a line, reads a whole reply, and checks the received code against the expected code. This is done in unit tests using local socket pairs. 
- sendCommand writes and sends one command. This is done in the unit test using local socket pairs.

The socket transport: 
- resolveAddr uses the name or address of the server and calls getaddrinfo. This is unit tested by resolving the address of localhost, 127.0.0.1, and a fake server (which should fail, and does).
- serverConnect uses the results from resolveAddr and calls connect to establish connection to the server. This is unit tested by establishing connection to localhost.
- getResponse uses recv to get a response from the server. This is unit tested using local socket pairs. 
- sendCommand uses send to send commands to the server. This is unit tested using local socket pairs.
- sendMessage uses send to send the message (body) to the server. This is unit tested using local socket pairs. 





---


## Build Output

This section was generated by running `make all` in the project root directory.

```bash
make[1]: Entering directory '/home/runner/work/cs525-p1/cs525-p1'
mkdir -p build/debug
cc -g -O0 -DDEBUG -fno-omit-frame-pointer -fsanitize=address -c src/main.c -o build/debug/main.c.o
mkdir -p build/debug
cc -g -O0 -DDEBUG -fno-omit-frame-pointer -fsanitize=address -c src/lab.c -o build/debug/lab.c.o
cc -g -O0 -DDEBUG -fno-omit-frame-pointer -fsanitize=address build/debug/main.c.o build/debug/lab.c.o -o build/debug/myapp_d -fsanitize=address
make[1]: Leaving directory '/home/runner/work/cs525-p1/cs525-p1'
make[1]: Entering directory '/home/runner/work/cs525-p1/cs525-p1'
mkdir -p build/release
cc -Wall -Wextra -O2 -fPIE -MMD -MP -Wformat -Wformat=2 -Wconversion -Wsign-conversion -Wimplicit-fallthrough -fstack-protector-strong -Werror=format-security -Werror=implicit -Werror=incompatible-pointer-types -Werror=int-conversion -c src/main.c -o build/release/main.c.o
mkdir -p build/release
cc -Wall -Wextra -O2 -fPIE -MMD -MP -Wformat -Wformat=2 -Wconversion -Wsign-conversion -Wimplicit-fallthrough -fstack-protector-strong -Werror=format-security -Werror=implicit -Werror=incompatible-pointer-types -Werror=int-conversion -c src/lab.c -o build/release/lab.c.o
cc -Wall -Wextra -O2 -fPIE -MMD -MP -Wformat -Wformat=2 -Wconversion -Wsign-conversion -Wimplicit-fallthrough -fstack-protector-strong -Werror=format-security -Werror=implicit -Werror=incompatible-pointer-types -Werror=int-conversion build/release/main.c.o build/release/lab.c.o -o build/release/myapp 
make[1]: Leaving directory '/home/runner/work/cs525-p1/cs525-p1'
make[1]: Entering directory '/home/runner/work/cs525-p1/cs525-p1'
mkdir -p build/tests
cc -g -O0 -DTEST -fprofile-arcs -ftest-coverage -c src/main.c -o build/tests/main.c.o
mkdir -p build/tests
cc -g -O0 -DTEST -fprofile-arcs -ftest-coverage -c src/lab.c -o build/tests/lab.c.o
mkdir -p build/tests/
cc -g -O0 -DTEST -fprofile-arcs -ftest-coverage -c tests/lab-test.c -o build/tests/lab-test.c.o
mkdir -p build/tests/harness/
cc -g -O0 -DTEST -fprofile-arcs -ftest-coverage -c tests/harness/unity.c -o build/tests/harness/unity.c.o
cc -g -O0 -DTEST -fprofile-arcs -ftest-coverage build/tests/main.c.o build/tests/lab.c.o build/tests/lab-test.c.o build/tests/harness/unity.c.o -o build/tests/myapp_t -fprofile-arcs -ftest-coverage
make[1]: Leaving directory '/home/runner/work/cs525-p1/cs525-p1'
make[1]: Entering directory '/home/runner/work/cs525-p1/cs525-p1'
mkdir -p build/debug-test
cc -g -O0 -DDEBUG -DTEST -fno-omit-frame-pointer -fsanitize=address -c src/main.c -o build/debug-test/main.c.o
mkdir -p build/debug-test
cc -g -O0 -DDEBUG -DTEST -fno-omit-frame-pointer -fsanitize=address -c src/lab.c -o build/debug-test/lab.c.o
mkdir -p build/debug-test/
cc -g -O0 -DDEBUG -DTEST -fno-omit-frame-pointer -fsanitize=address -c tests/lab-test.c -o build/debug-test/lab-test.c.o
mkdir -p build/debug-test/harness/
cc -g -O0 -DDEBUG -DTEST -fno-omit-frame-pointer -fsanitize=address -c tests/harness/unity.c -o build/debug-test/harness/unity.c.o
cc -g -O0 -DDEBUG -DTEST -fno-omit-frame-pointer -fsanitize=address build/debug-test/main.c.o build/debug-test/lab.c.o build/debug-test/lab-test.c.o build/debug-test/harness/unity.c.o -o build/debug-test/myapp_td -fsanitize=address
make[1]: Leaving directory '/home/runner/work/cs525-p1/cs525-p1'
Builds completed. You can run the application with: ./build/release/myapp
You can run the debug build with: ./build/debug/myapp_d
You can run the test build with: ./build/tests/myapp_t
You can run the debug-test build with: ./build/debug-test/myapp_td
```

---

## Coverage Report

This section was generated by running `make report` in the project root directory.

```bash
Error: -f <from> is required
Error: -t <to> is required
Error: server is required
Error: unknown option -x
Error: unexpected argument: mail.example.com
Error: option -f requires an argument
Error: unexpected argument: extra
getaddrinfo: Name or service not known
getaddrinfo: Servname not supported for ai_socktype
getaddrinfo: Name or service not known
Error: could not connect to server
Error: could not connect to server
Error: expected SMTP response 220, got 550
Error: invalid SMTP response
Error: invalid SMTP response: ABC Invalid response
Error: server closed connection
Error: invalid SMTP response: 22
Error: command is NULL
Error: NULL message parameter
Error: NULL message parameter
Error: NULL message parameter
Error: NULL message parameter
Error: message headers are too long
Setting up tests...
Tearing down tests...
tests/lab-test.c:1021:test_parseArgs_required_arguments:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1022:test_parseArgs_all_arguments:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1023:test_parseArgs_missing_from:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1024:test_parseArgs_missing_to:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1025:test_parseArgs_missing_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1026:test_parseArgs_unknown_option:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1027:test_parseArgs_missing_option_argument_a:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1028:test_parseArgs_missing_option_argument_b:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1029:test_parseArgs_extra_argument:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1030:test_resolveAddr_localhost:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1031:test_resolveAddr_ipv4_loopback:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1032:test_resolveAddr_invalid_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1033:test_resolveAddr_invalid_port:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1034:test_resolveAddr_empty_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1035:test_serverConnect_localhost:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1036:test_serverConnect_no_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1037:test_serverConnect_null_results:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1038:test_getResponse_correct_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1039:test_getResponse_wrong_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1040:test_getResponse_short_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1041:test_getResponse_multiline:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1042:test_getResponse_invalid_response:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1043:test_getResponse_connection_closed:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1044:test_getResponse_short_response:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1045:test_sendCommand_helo:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1046:test_sendCommand_mail_from:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1047:test_sendCommand_rcpt_to:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1048:test_sendCommand_data:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1049:test_sendCommand_quit:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1050:test_sendCommand_empty:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1051:test_sendCommand_null:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1052:test_sendMessage_sends_message:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1053:test_sendMessage_dot_stuffs_single_dot:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1054:test_sendMessage_null_parameters:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1055:test_sendMessage_headers_too_long:PASS

-----------------------
35 Tests 0 Failures 0 Ignored 
OK
./build/tests/myapp_t
Error: -f <from> is required
Error: -t <to> is required
Error: server is required
Error: unknown option -x
Error: unexpected argument: mail.example.com
Error: option -f requires an argument
Error: unexpected argument: extra
getaddrinfo: Name or service not known
getaddrinfo: Servname not supported for ai_socktype
getaddrinfo: Name or service not known
Error: could not connect to server
Error: could not connect to server
Error: expected SMTP response 220, got 550
Error: invalid SMTP response
Error: invalid SMTP response: ABC Invalid response
Error: server closed connection
Error: invalid SMTP response: 22
Error: command is NULL
Error: NULL message parameter
Error: NULL message parameter
Error: NULL message parameter
Error: NULL message parameter
Error: message headers are too long
Setting up tests...
Tearing down tests...
tests/lab-test.c:1021:test_parseArgs_required_arguments:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1022:test_parseArgs_all_arguments:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1023:test_parseArgs_missing_from:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1024:test_parseArgs_missing_to:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1025:test_parseArgs_missing_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1026:test_parseArgs_unknown_option:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1027:test_parseArgs_missing_option_argument_a:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1028:test_parseArgs_missing_option_argument_b:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1029:test_parseArgs_extra_argument:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1030:test_resolveAddr_localhost:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1031:test_resolveAddr_ipv4_loopback:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1032:test_resolveAddr_invalid_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1033:test_resolveAddr_invalid_port:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1034:test_resolveAddr_empty_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1035:test_serverConnect_localhost:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1036:test_serverConnect_no_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1037:test_serverConnect_null_results:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1038:test_getResponse_correct_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1039:test_getResponse_wrong_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1040:test_getResponse_short_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1041:test_getResponse_multiline:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1042:test_getResponse_invalid_response:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1043:test_getResponse_connection_closed:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1044:test_getResponse_short_response:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1045:test_sendCommand_helo:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1046:test_sendCommand_mail_from:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1047:test_sendCommand_rcpt_to:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1048:test_sendCommand_data:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1049:test_sendCommand_quit:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1050:test_sendCommand_empty:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1051:test_sendCommand_null:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1052:test_sendMessage_sends_message:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1053:test_sendMessage_dot_stuffs_single_dot:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1054:test_sendMessage_null_parameters:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1055:test_sendMessage_headers_too_long:PASS

-----------------------
35 Tests 0 Failures 0 Ignored 
OK
mkdir -p ./build/report/html
mkdir -p ./build/report/txt
gcovr -r . --html --html-details --exclude-directories build/tests/harness --exclude '.*main\.c$' --exclude '.*test\.c$' -o ./build/report/html/coverage_report.html
(INFO) Reading coverage data...

(INFO) Writing coverage report...

gcovr -r . --txt                 --exclude-directories build/tests/harness --exclude '.*main\.c$' --exclude '.*test\.c$'
(INFO) Reading coverage data...

(INFO) Writing coverage report...

------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines     Exec  Cover   Missing
------------------------------------------------------------------------------
src/lab.c                                    141      141   100%
------------------------------------------------------------------------------
TOTAL                                        141      141   100%
------------------------------------------------------------------------------
```

---

## Address Sanitizer Report

This section was generated by running `make leak-test` in the project root directory.

```bash
Error: -f <from> is required
Error: -t <to> is required
Error: server is required
Error: unknown option -x
Error: unexpected argument: mail.example.com
Error: option -f requires an argument
Error: unexpected argument: extra
getaddrinfo: Name or service not known
getaddrinfo: Servname not supported for ai_socktype
getaddrinfo: Name or service not known
Error: could not connect to server
Error: could not connect to server
Error: expected SMTP response 220, got 550
Error: invalid SMTP response
Error: invalid SMTP response: ABC Invalid response
Error: server closed connection
Error: invalid SMTP response: 22
Error: command is NULL
Error: NULL message parameter
Error: NULL message parameter
Error: NULL message parameter
Error: NULL message parameter
Error: message headers are too long
Setting up tests...
Tearing down tests...
tests/lab-test.c:1021:test_parseArgs_required_arguments:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1022:test_parseArgs_all_arguments:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1023:test_parseArgs_missing_from:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1024:test_parseArgs_missing_to:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1025:test_parseArgs_missing_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1026:test_parseArgs_unknown_option:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1027:test_parseArgs_missing_option_argument_a:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1028:test_parseArgs_missing_option_argument_b:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1029:test_parseArgs_extra_argument:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1030:test_resolveAddr_localhost:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1031:test_resolveAddr_ipv4_loopback:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1032:test_resolveAddr_invalid_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1033:test_resolveAddr_invalid_port:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1034:test_resolveAddr_empty_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1035:test_serverConnect_localhost:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1036:test_serverConnect_no_server:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1037:test_serverConnect_null_results:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1038:test_getResponse_correct_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1039:test_getResponse_wrong_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1040:test_getResponse_short_code:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1041:test_getResponse_multiline:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1042:test_getResponse_invalid_response:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1043:test_getResponse_connection_closed:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1044:test_getResponse_short_response:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1045:test_sendCommand_helo:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1046:test_sendCommand_mail_from:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1047:test_sendCommand_rcpt_to:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1048:test_sendCommand_data:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1049:test_sendCommand_quit:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1050:test_sendCommand_empty:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1051:test_sendCommand_null:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1052:test_sendMessage_sends_message:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1053:test_sendMessage_dot_stuffs_single_dot:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1054:test_sendMessage_null_parameters:PASS
Setting up tests...
Tearing down tests...
tests/lab-test.c:1055:test_sendMessage_headers_too_long:PASS

-----------------------
35 Tests 0 Failures 0 Ignored 
OK
```

---

## Src Files
### lab.c

```c

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

            // GCOVR_EXCL_START    
            default:
                return 1;
            // GCOVR_EXCL_STOP
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
        return 2;
    }

    return 0;
}

int serverConnect(struct addrinfo *results){

    struct addrinfo *current;
    int sockfd;

    for (current = results; current != NULL; current = current->ai_next) {

        sockfd = socket(current->ai_family, current->ai_socktype, current->ai_protocol);

        // GCOVR_EXCL_START
        if (sockfd == -1) {
            continue;
        }
        // GCOVR_EXCL_STOP

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
                return 2;
            }

            // GCOVR_EXCL_START
            if (bytes_read < 0) {
                perror("recv");
                return 2;
            }
            // GCOVR_EXCL_STOP

            buffer[position++] = c;

            if (c == '\n') {
                break;
            }
        }

        buffer[position] = '\0';

        if (position < 3) {
            fprintf(stderr, "Error: invalid SMTP response\n");
            return 2;
        }

        if (buffer[0] < '0' || buffer[0] > '9' ||
            buffer[1] < '0' || buffer[1] > '9' ||
            buffer[2] < '0' || buffer[2] > '9') {

            fprintf(stderr, "Error: invalid SMTP response: %s", buffer);
            return 2;
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
            return 2;
        }

        return 0;
    }
}


int sendCommand(int sockfd, const char *command){

    size_t command_len;
    size_t total_sent = 0;
    ssize_t bytes_sent = 0;

    if (command == NULL) {
        fprintf(stderr, "Error: command is NULL\n");
        return 2;
    }

    command_len = strlen(command);

    while (total_sent < command_len) {
        bytes_sent = send(sockfd,
                          command + total_sent,
                          command_len - total_sent,
                          0);

        // GCOVR_EXCL_START
        if (bytes_sent < 0) {
            perror("send");
            return 2;
        }   
        if (bytes_sent == 0) {
            fprintf(stderr, "Error: send returned 0\n");
            return 2;
        }
        // GCOVR_EXCL_STOP

        total_sent += (size_t)bytes_sent;
    }


    // GCOVR_EXCL_START
    if (send(sockfd, "\r\n", 2, 0) != 2) {
        perror("send");
        return 2;
    }
    // GCOVR_EXCL_STOP

    return 0;
}



int sendMessage(int sockfd, const char *from, const char *to, const char *subject, const char *body){

    const char *current;
    const char *line_start;
    const char *line_end;
    size_t line_length;
    size_t total_sent;
    ssize_t bytes_sent;

    char header[1024];
    int header_length;

    if (from == NULL || to == NULL || subject == NULL || body == NULL) {
        fprintf(stderr, "Error: NULL message parameter\n");
        return 1;
    }

    header_length = snprintf(
        header,
        sizeof(header),
        "From: %s\r\n"
        "To: %s\r\n"
        "Subject: %s\r\n"
        "\r\n",
        from,
        to,
        subject
    );

    if (header_length < 0 || (size_t)header_length >= sizeof(header)) {
        fprintf(stderr, "Error: message headers are too long\n");
        return 2;
    }

    total_sent = 0;

    while (total_sent < (size_t)header_length) {
        bytes_sent = send(
            sockfd,
            header + total_sent,
            (size_t)header_length - total_sent,
            0
        );

        // GCOVR_EXCL_START
        if (bytes_sent < 0) {
            perror("send");
            return 2;
        }

        if (bytes_sent == 0) {
            fprintf(stderr, "Error: send returned 0\n");
            return 2;
        }
        // GCOVR_EXCL_STOP

        total_sent += (size_t)bytes_sent;
    }

    current = body;

    while (*current != '\0') {
        line_start = current;

        while (*current != '\0' && *current != '\n') {
            current++;
        }

        line_end = current;

        line_length = (size_t)(line_end - line_start);

        if (line_length > 0 &&
            line_start[line_length - 1] == '\r') {
            line_length--;
        }

        if (line_length > 0 && line_start[0] == '.') {
            char dot = '.';

            // GCOVR_EXCL_START
            if (send(sockfd, &dot, 1, 0) != 1) {
                perror("send");
                return 2;
            }
            // GCOVR_EXCL_STOP
        }

        total_sent = 0;

        while (total_sent < line_length) {
            bytes_sent = send(
                sockfd,
                line_start + total_sent,
                line_length - total_sent,
                0
            );

            // GCOVR_EXCL_START
            if (bytes_sent < 0) {
                perror("send");
                return 2;
            }

            if (bytes_sent == 0) {
                fprintf(stderr, "Error: send returned 0\n");
                return 2;
            }
            // GCOVR_EXCL_STOP

            total_sent += (size_t)bytes_sent;
        }

        // GCOVR_EXCL_START
        if (send(sockfd, "\r\n", 2, 0) != 2) {
            perror("send");
            return 2;
        }
        // GCOVR_EXCL_STOP

        if (*current == '\n') {
            current++;
        }
    }

    // GCOVR_EXCL_START
    if (send(sockfd, "\r\n.\r\n", 5, 0) != 5) {
        perror("send");
        return 2;
    }
    // GCOVR_EXCL_STOP

    return 0;
}



```

### lab.h

```c

#ifndef LAB_H
#define LAB_H

#define _POSIX_C_SOURCE 200112L

#include <netdb.h>

/** * @brief Returns a greeting message.
 *
 * This function returns a string that contains a greeting message.
 * The string is allocated with malloc and should be freed by the caller.
 * @param name The name to include in the greeting.
 * @return A greeting string.
 */
char* get_greeting(const char* restrict name);

/** * @brief Parses command line arguments
 * 
 * This function parses the command line arguments with information to connect and send to the server
 * @param argc number of arguments
 * @param argv the input string
 * @param from the envelope sender
 * @param to the envelope recipient
 * @param subject the subject line
 * @param body the body of the message
 * @param port the port number of the recipient
 * @param helo_host host name sent with HELO
 * @param server the host name or address or the mail server
 * @return 0 for success nonzero for error
 */
int parseArgs(int argc, char **argv, char **from, char **to, char **subject, char **body,
               char **port, char **helo_host, char **server);

/** * @brief Resolves the name of the server
 * 
 * This function resolves the name of the server using getaddrinfo
 * @param server the name of the recipient given by the user
 * @param port the port number of the recipient given by the user
 * @param results the resulting server name
 */
int resolveAddr(const char *server, const char *port, struct addrinfo **results);

/** * @brief Creates a connection to the server
 *  
 * This function opens a TCP connection to the server named on the command line
 * @param results the name of the server to connect to
 * @return the socket used for the connection or -1 for failure
 */
int serverConnect(struct addrinfo *results);

/** * @brief Reads the response from the server
 * 
 * This function reads the response from the socket and obtains the SMTP response code
 * @param sockfd the socket used for the connection
 * @param expected_code the code expected from the server
 * @return 0 for success nonzero for failure //FIXME
 */
int getResponse(int sockfd, int expected_code);

/** * @brief Sends a command to the server
 * 
 * This function sends a command to the server, including HELO, MAIL FROM, RCPT TO, DATA, and QUIT
 * @param sockfd the socket used for the connection
 * @param command the command to send to the server
 * @return 0 for success, nonzero for fail
 */
int sendCommand(int sockfd, const char *command);

/** * @brief Sends a message to the server
 * 
 * This function sends the message to the server that follows the DATA command. 
 * @param sockfd the socket used for the connection
 * @param from the sender to be displayed in the message
 * @param to the receiver to be displayed in the message
 * @param subject the subject of the message
 * @param body the body of the message
 * @return 0 for success, nonzero for fail //FIXME
 */
int sendMessage(int sockfd, const char *from, const char *to, const char *subject, const char *body);




#endif // LAB_H

```

### main.c

```c

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
```

## Tests Files
### lab-test.c

```c

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

void test_parseArgs_missing_option_argument_a(void){

    char *argv[] = {
        "myapp",
        "-f", "alice@example.com",
        "-t", "bob@example.com",
        "-s", "Test Subject",
        "-b", "Hello Bob!",
        "-p", 
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

    TEST_ASSERT_NOT_EQUAL(0, result);
}

void test_parseArgs_missing_option_argument_b(void){

    char *argv[] = {
        "myapp",
        "-f"
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

void test_getResponse_short_code(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    const char *response =
        "2\n";

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

//sendCommand tests

void test_sendCommand_helo(void){

    int sockets[2];
    char buffer[1024];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(sockets[0], "HELO localhost");

    TEST_ASSERT_EQUAL_INT(0, result);

    ssize_t bytes_read = recv(
        sockets[1],
        buffer,
        sizeof(buffer) - 1,
        0
    );

    TEST_ASSERT_GREATER_THAN(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(
        "HELO localhost\r\n",
        buffer
    );

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendCommand_mail_from(void){

    int sockets[2];
    char buffer[1024];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(
        sockets[0],
        "MAIL FROM:<alice@example.com>"
    );

    TEST_ASSERT_EQUAL_INT(0, result);

    ssize_t bytes_read = recv(
        sockets[1],
        buffer,
        sizeof(buffer) - 1,
        0
    );

    TEST_ASSERT_GREATER_THAN(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(
        "MAIL FROM:<alice@example.com>\r\n",
        buffer
    );

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendCommand_rcpt_to(void){

    int sockets[2];
    char buffer[1024];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(
        sockets[0],
        "RCPT TO:<bob@example.com>"
    );

    TEST_ASSERT_EQUAL_INT(0, result);

    ssize_t bytes_read = recv(
        sockets[1],
        buffer,
        sizeof(buffer) - 1,
        0
    );

    TEST_ASSERT_GREATER_THAN(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(
        "RCPT TO:<bob@example.com>\r\n",
        buffer
    );

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendCommand_data(void){

    int sockets[2];
    char buffer[1024];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(sockets[0], "DATA");

    TEST_ASSERT_EQUAL_INT(0, result);

    ssize_t bytes_read = recv(
        sockets[1],
        buffer,
        sizeof(buffer) - 1,
        0
    );

    TEST_ASSERT_GREATER_THAN(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(
        "DATA\r\n",
        buffer
    );

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendCommand_quit(void){

    int sockets[2];
    char buffer[1024];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(sockets[0], "QUIT");

    TEST_ASSERT_EQUAL_INT(0, result);

    ssize_t bytes_read = recv(
        sockets[1],
        buffer,
        sizeof(buffer) - 1,
        0
    );

    TEST_ASSERT_GREATER_THAN(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(
        "QUIT\r\n",
        buffer
    );

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendCommand_empty(void){

    int sockets[2];
    char buffer[1024];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(sockets[0], "");

    TEST_ASSERT_EQUAL_INT(0, result);

    ssize_t bytes_read = recv(
        sockets[1],
        buffer,
        sizeof(buffer) - 1,
        0
    );

    TEST_ASSERT_EQUAL_INT(2, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(
        "\r\n",
        buffer
    );

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendCommand_null(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    int result = sendCommand(sockets[0], NULL);

    TEST_ASSERT_NOT_EQUAL(0, result);

    close(sockets[0]);
    close(sockets[1]);
}

//sendMessage tests

void test_sendMessage_sends_message(void){

    int sockets[2];
    char buffer[1024];
    ssize_t bytes_read;

    const char *from = "alice@example.com";
    const char *to = "bob@example.com";
    const char *subject = "Test message";
    const char *body = "Hello Bob!\r\nThis is a test.";

    const char *expected =
        "From: alice@example.com\r\n"
        "To: bob@example.com\r\n"
        "Subject: Test message\r\n"
        "\r\n"
        "Hello Bob!\r\n"
        "This is a test.\r\n"
        "\r\n.\r\n";

    TEST_ASSERT_EQUAL_INT(0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    TEST_ASSERT_EQUAL_INT(
        0,
        sendMessage(sockets[0], from, to, subject, body)
    );

    bytes_read = recv(sockets[1], buffer, sizeof(buffer) - 1, 0);

    TEST_ASSERT_GREATER_THAN_INT(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendMessage_dot_stuffs_single_dot(void){

    int sockets[2];
    char buffer[1024];
    ssize_t bytes_read;

    const char *from = "alice@example.com";
    const char *to = "bob@example.com";
    const char *subject = "Dot test";
    const char *body =
        "First line\r\n"
        ".\r\n"
        "Last line";

    const char *expected =
        "From: alice@example.com\r\n"
        "To: bob@example.com\r\n"
        "Subject: Dot test\r\n"
        "\r\n"
        "First line\r\n"
        "..\r\n"
        "Last line\r\n"
        "\r\n.\r\n";

    TEST_ASSERT_EQUAL_INT(0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    TEST_ASSERT_EQUAL_INT(
        0,
        sendMessage(sockets[0], from, to, subject, body)
    );

    bytes_read = recv(sockets[1], buffer, sizeof(buffer) - 1, 0);

    TEST_ASSERT_GREATER_THAN_INT(0, bytes_read);

    buffer[bytes_read] = '\0';

    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    close(sockets[0]);
    close(sockets[1]);
}


void test_sendMessage_null_parameters(void){

    int sockets[2];

    TEST_ASSERT_EQUAL_INT(0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));

    TEST_ASSERT_NOT_EQUAL(
        0,
        sendMessage(
            sockets[0],
            NULL,
            "bob@example.com",
            "Test",
            "Hello"
        )
    );

    TEST_ASSERT_NOT_EQUAL(
        0,
        sendMessage(
            sockets[0],
            "alice@example.com",
            NULL,
            "Test",
            "Hello"
        )
    );

    TEST_ASSERT_NOT_EQUAL(
        0,
        sendMessage(
            sockets[0],
            "alice@example.com",
            "bob@example.com",
            NULL,
            "Hello"
        )
    );

    TEST_ASSERT_NOT_EQUAL(
        0,
        sendMessage(
            sockets[0],
            "alice@example.com",
            "bob@example.com",
            "Test",
            NULL
        )
    );

    close(sockets[0]);
    close(sockets[1]);
}

void test_sendMessage_headers_too_long(void)
{
    int sockets[2];

    TEST_ASSERT_EQUAL_INT(
        0,
        socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)
    );

    char from[1000];

    memset(from, 'A', sizeof(from) - 1);
    from[sizeof(from) - 1] = '\0';

    const char *to = "bob@example.com";
    const char *subject = "Test";
    const char *body = "Hello";

    int result = sendMessage(
        sockets[0],
        from,
        to,
        subject,
        body
    );

    TEST_ASSERT_EQUAL_INT(2, result);

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
  RUN_TEST(test_parseArgs_missing_option_argument_a);
  RUN_TEST(test_parseArgs_missing_option_argument_b);
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
  RUN_TEST(test_getResponse_short_code);
  RUN_TEST(test_getResponse_multiline);
  RUN_TEST(test_getResponse_invalid_response);
  RUN_TEST(test_getResponse_connection_closed);
  RUN_TEST(test_getResponse_short_response);
  RUN_TEST(test_sendCommand_helo);
  RUN_TEST(test_sendCommand_mail_from);
  RUN_TEST(test_sendCommand_rcpt_to);
  RUN_TEST(test_sendCommand_data);
  RUN_TEST(test_sendCommand_quit);
  RUN_TEST(test_sendCommand_empty);
  RUN_TEST(test_sendCommand_null);
  RUN_TEST(test_sendMessage_sends_message);
  RUN_TEST(test_sendMessage_dot_stuffs_single_dot);
  RUN_TEST(test_sendMessage_null_parameters);
  RUN_TEST(test_sendMessage_headers_too_long);
  return UNITY_END();
}

```

## Scripts Files
Report generated on 09/17/2026 at 23:04:18


---

## End of Report

SHA-256 Hash of the report: 7ae585b6603f42c3637ca7e94db95b84dea0ca0ac642017a612823112cbf347b

Do not edit the generated report. Any changes will be reported as academic dishonesty

---
## GitHub Info
- GitHub repo name: 2213amanda/cs525-p1
- The repository visibility is public.
- The workflow was triggered by 2213amanda
