#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

static const int MAXPENDING = 5;

int SetupTCPServerSocket(const char *service){
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0 ,sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_flags= AI_PASSIVE;
	addrCriteria.ai_socktype= SOCK_STREAM;;
	addrCriteria.ai_protocol = IPPROTO_TCP;

	struct addrinfo *servAddr;
	int rtnVal = getaddrinfo(NULL,service,&addrCriteria,&servAddr);
	if(rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed",gai_strerror(rtnVal));	

	int servSock = -1;
	struct addrinfo * addr ;
	for(addr = servAddr; addr != NULL; addr = addr->ai_next){
		servSock = socket(addr->ai_family,addr->ai_socktype,addr->ai_protocol)	;
		printf("socket() return %d\n", servSock);
		int rep = 1;
		if((setsockopt(servSock,SOL_SOCKET,SO_REUSEADDR,&rep,sizeof(rep))) !=0)
			DieWithSystemMessage("setsockopt() failed");	

		if((bind(servSock,addr->ai_addr,addr->ai_addrlen) != 0)) {
			perror("bind() failed");	
			goto out;
		}
		if(	(listen(servSock,MAXPENDING) != 0)){
			perror("listen() failed");	
			goto out;
		}
		
		struct sockaddr_storage localAddr;		
		socklen_t addrSize = sizeof(localAddr);
		if(getsockname(servSock,(struct sockaddr *) &localAddr,&addrSize) < 0)
			DieWithSystemMessage("getsockname() failed");
		fputs("Binding to ", stdout);
		PrintSocketAddress((struct sockaddr *) &localAddr,stdout);
		fputc('\n',stdout);
		break;

		out:	
		close(socket);
		servSock = -1;
	}
	freeaddrinfo(servAddr);
	return servSock;
	
}

int AcceptTCPConnection(int servSock) {
  struct sockaddr_storage clntAddr; // Client address
  // Set length of client address structure (in-out parameter)
  socklen_t clntAddrLen = sizeof(clntAddr);

  // Wait for a client to connect
  int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
  if (clntSock < 0)
    DieWithSystemMessage("accept() failed");

  // clntSock is connected to a client!

  fputs("Handling client ", stdout);
  PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
  fputc('\n', stdout);

  return clntSock;
}

