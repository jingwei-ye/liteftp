#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"
static const int MAXPENDING = 5;
static const int BUFSIZE= 1000;

void HandleTCPClient(int clntSock){
	char buffer[BUFSIZE];
	ssize_t numBytesRcvd = recv(clntSock,buffer,BUFSIZE,0);
	if(numBytesRcvd < 0)
		DieWithSystemMessage("recv() failed");
	while(numBytesRcvd > 0){
		ssize_t numBytesSend = send(clntSock,buffer,numBytesRcvd,0);
		if(numBytesRcvd < 0)
			DieWithSystemMessage("send() fail");
		else if(numBytesSend != numBytesSend)
			DieWithSystemMessage("send() unexpected number of bytes");
		numBytesRcvd = recv(clntSock,buffer,BUFSIZE,0);
		if(numBytesRcvd < 0)
			DieWithSystemMessage("recv() failed");
	}
	close(clntSock);
}

int main(int argc,char **argv){
	printf("argc:%d\n",argc );
	if(argc != 2){
		DieWithUserMessage("Parameter(s)", "<Server Port>")	;
	}
	in_port_t servPort = atoi(argv[1]);
	int servSock;
	if((servSock= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0){
		DieWithSystemMessage("socket() fail");	
	}
	printf("port:%d\n" ,servPort);
	struct sockaddr_in servAddr;
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr= htonl(INADDR_ANY);
	servAddr.sin_port= htons(servPort);
	
	if(bind(servSock,(struct sockaddr *) &servAddr,sizeof(servAddr)) < 0)
		DieWithSystemMessage("bind() failed");

	if(listen(servSock,MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	for(;;){
		struct sockaddr_in clntAddr;	
		socklen_t clntAddrLen = sizeof(clntAddr);
		printf("begin accept. sock:%d\n", servSock);
		int clntSock = accept(servSock,(struct sockaddr*) & clntAddr, &clntAddrLen);
		printf("accept. clntSock:%d\n", clntSock);
		if(clntSock < 0 )
			DieWithSystemMessage("accepted failed");	
		char clntName[INET_ADDRSTRLEN];
		if(inet_ntop(AF_INET,&clntAddr.sin_addr.s_addr,clntName,sizeof(clntName)) != NULL)
			printf("Handling client %s/%d\n",clntName,ntohs(clntAddr.sin_port));
		else
			printf("unable to get client address");

		HandleTCPClient(clntSock);
	}
}
