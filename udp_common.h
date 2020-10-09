#pragma once


#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>


void fail( char const * where ) __attribute(( noreturn ));
int  new_bound_udp_socket( char const * host, char const * service );
void parse_server( char const * host, char const * service,
                   struct sockaddr_in * psai );


