#include "udp_common.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void send_packet( int sd, char const * host, char const * service );
void usage( char const * argv0 ) __attribute(( noreturn ));


int main( int argc, char const * argv[] ) {

    int sd;

    if ( argc < 4 )
        usage( argv[ 0 ] );

    sd = new_bound_udp_socket( "0.0.0.0", argv[ 1 ] );

    for ( int i = 3 ; i < argc; i += 1 )
        send_packet( sd, argv[ i ], argv[ 2 ] );

    close( sd );

    return EXIT_SUCCESS;

}


void send_packet( int sd, char const * host, char const * service ) {

    struct sockaddr_in sai;
    ssize_t            ssz;

    parse_server( host, service, & sai );

    printf( "Server: %s:%s\n", host, service );

    ssz = sendto( sd, & sai, sizeof( sai ), 0, ( struct sockaddr * ) & sai,
                  sizeof( sai ) );
    if ( -1 == ssz )
        fail( "sendto() failed" );


}


void usage( char const * argv0 ) {
    printf( "YourPrompt> %s <client-port> <server-port> <server-ip...>\n",
            argv0 );
    exit( EXIT_FAILURE );
}


