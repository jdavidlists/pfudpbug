#include "udp_common.h"


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void recv_packet( int sd );
void usage( char const * argv0 ) __attribute(( noreturn ));


int main( int argc, char const * argv[] ) {

    int          sd;
    char const * host;
    char const * service;

    if ( argc < 2 || argc > 3 )
        usage( argv[ 0 ] );

    if ( argc == 2 ) {
        host = "127.0.0.1";
        service = argv[ 1 ];
    } else {
        host = argv[ 1 ];
        service = argv[ 2 ];
    }

    sd = new_bound_udp_socket( host, service );

    while ( true )
        recv_packet( sd );

    return EXIT_SUCCESS;

}


void recv_packet( int sd ) {

    ssize_t            ssz;
    struct sockaddr_in saiBuffer;
    struct sockaddr_in saiClient;
    socklen_t          lenClient = sizeof( saiClient );


    ssz = recvfrom( sd, & saiBuffer, sizeof( saiBuffer ), 0,
                    ( struct sockaddr * ) & saiClient, & lenClient );
    if ( -1 == ssz )
        fail( "recvfrom() failed" );

    if ( lenClient != sizeof( saiClient ) )
        fail( "Address buffer mismatch" );

    printf( "Received from %s:%hu for ",
            inet_ntoa( saiClient.sin_addr ), ntohs( saiClient.sin_port ) );
    printf( "%s:%hu.\n",
            inet_ntoa( saiBuffer.sin_addr ), ntohs( saiBuffer.sin_port ) );

}


void usage( char const * argv0 ) {
    printf( "YourPrompt> %s [server-address] <server-port>\n", argv0 );
    exit( EXIT_FAILURE );
}


