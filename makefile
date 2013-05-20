#AddressUtility.c  DieWithMessage.c  GetAddrInfo.c     Practical.h       TCPEchoServer4.o  
#AddressUtility.o  DieWithMessage.o  GetAddrInfo.o     TCPEchoServer4.c  makefile   
#OBJS = 
#EXEC = GetAddressInfo 
#------ coustomer definitions

#OBJS = AddressUtility.o DieWithMessage.o   TCPClientUtility.o TCPServerUtility.o
OBJS = AddressUtility DieWithMessage   TCPClientUtility TCPServerUtility

ALL_OBJS = $(OBJS:%=%.o)

%.o: %.c
	gcc -c $<  -o $@ 
#TCPEchoServer4 : TCPEchoServer4.o AddressUtility.o DieWithMessage.o Practical.h
#	gcc -o TCPEchoServer4  TCPEchoServer4.o AddressUtility.o DieWithMessage.o

DO_OBJS = gcc -c -o $@.o $@.c
#DO_OBJS = gcc -c -o $@.o $@.c; touch $@
#DO_EXEC = gcc -s -o $@ $(ALL_OBJ)

  #------ now compile


TCPEchoServer4 : TCPEchoServer4.o $(ALL_OBJS) Practical.h
	gcc -o TCPEchoServer4  TCPEchoServer4.o $(ALL_OBJS)

LiteFtp: LiteFtp.o $(ALL_OBJS) Practical.h
	gcc -o LiteFtp LiteFtp.o $(ALL_OBJS)

#GetAddrInfo : GetAddrInfo.o AddressUtility.o DieWithMessage.o Practical.h
#	gcc -o GetAddrInfo GetAddrInfo.o AddressUtility.o DieWithMessage.o

#GetAddrInfo : $(OBJS) Practical.h
#	gcc -o GetAddrInfo $(OBJS)

#LiteFtp: LiteFtp.o $(OBJS) Practical.h
#	gcc -o LiteFtp LiteFtp.o $(OBJS)

