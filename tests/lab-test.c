#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"


void setUp(void) {
  printf("Setting up tests...\n");
}

void tearDown(void) {
  printf("Tearing down tests...\n");
}

void test_get_greeting(void) {
  char *greeting = get_greeting("Alice");
  TEST_ASSERT_NOT_NULL(greeting);
  TEST_ASSERT_EQUAL_STRING("Hello, Alice!", greeting);
  free(greeting); // Free the allocated memory for the greeting

  greeting = get_greeting(NULL);
  TEST_ASSERT_NULL(greeting);

  greeting = get_greeting("");
  TEST_ASSERT_NOT_NULL(greeting);
  TEST_ASSERT_EQUAL_STRING("Hello, !", greeting);
  free(greeting);
}

/*
3 layers

1 - Pure protocol helpers. Functions that take strings and return strings or 
status codes: parse a reply line into its code, decide whether a reply line 
is the final one, build a command line, dot stuff a body, build the DATA payload. 
No I/O anywhere in here.

2 - The session, over a transport you can swap out. Reading a line, reading a whole 
reply, writing, sending one command and checking its code, and running the entire 
session. These do all their reading and writing through a pair of function 
pointers (a read and a write callback plus a context pointer) rather than calling 
recv and send directly.

3 - The socket transport. Thin wrappers over getaddrinfo, connect, recv and send that 
satisfy those two callbacks.
*/

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_greeting);
  return UNITY_END();
}
