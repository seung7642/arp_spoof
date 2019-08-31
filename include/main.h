#ifndef _MAIN_H
#define _MAIN_H

// C Headers
#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

// glibc 2.1 is missing the ifr_newname macro in <net/if.h>
#ifndef ifr_newname
#define ifr_newname ifr_ifru.ifru_slave
#endif

// Parameter Flag
#define IN
#define OUT

#endif
