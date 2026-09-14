#include "lab.h"
#include <stdio.h>
#include <stdlib.h>


char *get_greeting(const char *restrict name)
{
  if (name == NULL)
  {
    return NULL;
  }

  // Allocate memory for the greeting message
  int length = snprintf(NULL, 0, "Hello, %s!", name);
  if (length < 0) // GCOVR_EXCL_START
  {
    return NULL; // snprintf failed
  } // GCOVR_EXCL_STOP

  //Casting is safe here because we know length is non-negative
  size_t alloc_size = (size_t) length + 1; // +1 for the null terminator
  char *greeting = malloc( alloc_size);


  if (greeting == NULL) // GCOVR_EXCL_START
  {
    return NULL; // Memory allocation failed
  }  // GCOVR_EXCL_STOP


  // Create the greeting message
  snprintf(greeting, alloc_size, "Hello, %s!", name);

  return greeting;
}

int parseArgs(int argc, char **argv, char **from, char **to, char **subject, char **body, 
              char **port, char **helo_host, char **server)
{
    return 0;
}

int resolveAddr(const char *server, const char *port, struct addrinfo **results)
{
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
