#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "Practical.h"


int main(int argc, char ** argv){
	if(argc != 3){
		DieWithUserMessage("Parameters:","<Address> <Port>");	
	}
	char *addrString = argv[1];
	char *portString = argv[2];
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype= SOCK_STREAM;
	addrCriteria.ai_protocol= IPPROTO_TCP;

	struct addrinfo *addrList;
	int rntVal = getaddrinfo(addrString,portString,&addrCriteria,&addrList);
	if(rntVal != 0){
		DieWithUserMessage("getaddrinfo() fail ",gai_strerror(rntVal));	
	}
	struct addrinfo * addr;
	for(addr = addrList; addr != NULL; addr = addr->ai_next){
		PrintSocketAddress(addr->ai_addr,stdout);			
		fputc('\n',stdout);
	}
	freeaddrinfo(addrList);
	exit(0);
}
