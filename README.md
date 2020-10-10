# pfudpbug
Code to exercise a bug related to FreeBSD PF redirecting UDP packets.

It has been tested on 11.4 and 12.1; the bug occurs in both cases.

This test runs on three FreeBSD systems: fb1, fb2, and fb3.

fb1 (client):
- em0: DHCP (used for remote access during test)
- em1: 10.0.0.1/24 (client-network)
- static routes:
  - 10.255.255.0/24 via 10.0.0.2
  - 172.16.0.0/12 via 10.0.0.2
- traceroute:
  - traceroute -n -i em1
- command line:
  - make test-client

fb2 (pf gateway):
- em0: DHCP (used for remote access during test)
- fb2 em1: 10.0.0.2/24 (client-network)
- fb2 em2: 10.255.255.2/24 (server-network)
- pf config: fb2.pf.conf in this repository
- traceroutes:
  - traceroute -n -i em1
  - traceroute -n -i em2
  - traceroute -n -i pflog0

fb3 (server):
- em0: DHCP (used for remote access during test)
- em1: 10.255.255.3/24 (server-network)
- static routes:
  - 10.0.0.0/24 via 10.255.255.2
- traceroute:
  - traceroute -n -i em2
- command line:
  - make test-server

Expected behavior:
- Client sends 4 UDP packets from 10.0.0.1 to four different addresses in 172.16.0.0/12.
- Gateway receives 4 UDP packets from client.
- PF redirects packets to server at 10.255.255.3.
- Gateway sends 4 UDP packets to server.
- fb2's em2 Opkts interface counter increases by 4.
- Server receives 4 UDP packets from the gateway.

Actual behavior:
- Client sends 4 UDP packets from 10.0.0.1 to four different addresses in 172.16.0.0/12.
- Gateway receives 4 UDP packets from client.
- PF redirects packets to server at 10.255.255.3.
- Gateway sends 1 UDP packet to server.
- Remaining three packets appear in fb2 traceroutes on em1 and pflog0, but not em2.
- fb2's em2 Opkts interface counter increases by 1.
- Server receives 1 UDP packet from the gateway.




