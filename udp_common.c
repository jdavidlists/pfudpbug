#define _POSIX_C_SOURCE 200112L


#include "udp_common.h"


#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void fail( char const * where ) {
    perror( where );
    exit( EXIT_FAILURE );
}


int new_bound_udp_socket( char const * host, char const * service ) {

    int                sd;
    struct sockaddr_in sai;

    parse_server( host, service, & sai );

    sd = socket( sai.sin_family, SOCK_DGRAM, 0 );
    if ( -1 == sd )
        fail( "socket() failed" );

    if ( bind( sd, ( struct sockaddr * ) & sai, sizeof( sai ) ) < 0 )
        fail( "bind() failed" );

    return sd;

}


void parse_server( char const * host, char const * service,
                   struct sockaddr_in * psai ) {

    int               i;
    struct addrinfo   aiHints;
    struct addrinfo * pai;

    memset( & aiHints, 0, sizeof( aiHints ) );
    aiHints.ai_family = AF_INET;
    aiHints.ai_socktype = SOCK_DGRAM;

    i = getaddrinfo( host, service, & aiHints, & pai );
    if ( 0 == i ) {
        * psai = * ( struct sockaddr_in * ) pai->ai_addr;
        freeaddrinfo( pai );
        return;
    }

    fprintf( stderr, "Unable to parse: %s:%s (%s)\n",
             ( NULL == host ) ? "(null)" : host,
             ( NULL == service ) ? "(null)" : service,
             gai_strerror( i ) );
    exit( EXIT_FAILURE );

}



