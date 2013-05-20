#include "Practical.h"

static int BUFSIZE = 1000;
void HandleTCPClient(int clntSock){
	printf("begin HandleTCPClient(). clntSock:%d\n",clntSock);
	char str[1024];
	sprintf(str,"220 wocao\r\n\0");
	send(clntSock,str,100,0);

	char buffer[BUFSIZE];
	ssize_t numBytesRcvd = recv(clntSock,buffer,BUFSIZE,0);
	if(numBytesRcvd < 0)
		DieWithSystemMessage("recv() failed");
	while(numBytesRcvd > 0){ 
		printf("recv:%s\n", buffer);
		//ssize_t numBytesSend = send(clntSock,buffer,numBytesRcvd,0);
		//if(numBytesRcvd < 0)
		//  DieWithSystemMessage("send() fail");
		//else if(numBytesSend != numBytesSend)
		//  DieWithSystemMessage("send() unexpected number of bytes");
		numBytesRcvd = recv(clntSock,buffer,BUFSIZE,0);
		if(numBytesRcvd < 0)
			DieWithSystemMessage("recv() failed");
	}
	close(clntSock);
}
void run(char * service){
	//char  service[] = "ftp";
	printf("service:%s\n",service);
	int lstnSock = SetupTCPServerSocket(service);
	printf("lstnSock:%d\n",lstnSock );

	int clntSock = AcceptTCPConnection(lstnSock);
	printf("clntSock:%d\n",clntSock);
	if(clntSock < 0){
		DieWithSystemMessage("AcceptTCPConnection() fail")	;
	}
	HandleTCPClient(clntSock);
}

int main(int argc,char ** argv){
	int port = atoi(argv[1]);
	run(argv[1]);
}
