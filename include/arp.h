#ifndef _ARP_H
#define _ARP_H

#include <main.h>

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

int getLocalMacAddress(char* interfaceName, OUT uint8_t* localMacAddress);
int getLocalIpAddress(char* interfaceName, OUT uint8_t* localIpAddress);
int getMacAddress(IN pcap_t* handle, IN uint8_t* localIpAddress, IN uint8_t* localMacAddress, IN uint8_t* targetIpAddress, OUT uint8_t* targetMacAddress);
int receiveMacAddress(IN pcap_t* handle, IN uint8_t* localIpAddress, IN uint8_t* localMacAddress, IN uint8_t* targetIpAddress, OUT uint8_t* targetMacAddress);
int infectSender(pcap_t* handle, uint8_t* localMacAddress, ArpSession arpSession); 

#endif
