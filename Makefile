# vim: set noexpandtab:

CFLAGS=	-std=c1x -Wall -Wextra -pedantic -Wc++-compat -Wconversion -Wcast-qual -Wshadow -Wpointer-arith -Wstrict-prototypes
CLIENT_OBJS=	udp_client.o udp_common.o
SERVER_OBJS=	udp_server.o udp_common.o
TARGETS=	udp_client udp_server


all: ${TARGETS}

clean:
	rm -f core *.core ${CLIENT_OBJS} ${SERVER_OBJS} ${TARGETS}

test-client: all
	./udp_client 23456 12345 172.16.0.1 172.16.0.2 172.16.0.3 172.16.0.4

test-server: all
	./udp_server 10.255.255.3 12345

udp_client: ${CLIENT_OBJS}
	${CC} -o $@ ${CLIENT_OBJS}

udp_server: ${SERVER_OBJS}
	${CC} -o $@ ${SERVER_OBJS}

udp_client.o: udp_client.c udp_common.h
udp_common.o: udp_common.c udp_common.h
udp_server.o: udp_server.c udp_common.h

