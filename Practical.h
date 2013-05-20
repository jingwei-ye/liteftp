#ifndef PRACTICAL_H_
#define PRACTICAL_H_

#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>

// Handle error with user msg
void DieWithUserMessage(const char *msg, const char *detail);
// Handle error with sys msg
void DieWithSystemMessage(const char *msg);

void PrintSocketAddress(const struct sockaddr *address, FILE *stream);

int SetupTCPClientSocket(const char * host, const char * service);
int SetupTCPServerSocket(const char *service);

int AcceptTCPConnection(int servSock);
#endif // PRACTICAL_H_
