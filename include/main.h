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

// Constants
#define PROMISCUOUS 1

#define ETHERTYPE_IP 0x8000
#define ETHERTYPE_ARP 0x0806

#define ARP_HW_TYPE 0x0001
#define ARP_PROTO_TYPE 0x0800
#define ARP_HW_LEN 0x06
#define ARP_PROTO_LEN 0x04
#define ARP_OPCODE 0x0001

#pragma pack(push, 1)
typedef struct _ArpSession {
	uint8_t senderMacAddress[6];
	uint8_t senderIpAddress[4];
	uint8_t targetMacAddress[6];
	uint8_t targetIpAddress[4];
} ArpSession;

typedef struct _EtherHeader {
	uint8_t destinationMacAddress[6];
	uint8_t sourceMacAddress[6];
	uint16_t type;
} EtherHeader;

typedef struct _ArpHeader {
	uint16_t hardwareType;
	uint16_t protocolType;
	uint8_t hardwareLength;
	uint8_t protocolLength;
	uint16_t opcode;
	uint8_t senderHardwareAddress[6];
	uint8_t senderProtocolAddress[4];
	uint8_t targetHardwareAddress[6];
	uint8_t targetProtocolAddress[4];
} ArpHeader;
#pragma pack(pop)

#endif
