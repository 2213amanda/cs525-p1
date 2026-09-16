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
