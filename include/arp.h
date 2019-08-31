#ifndef _ARP_H
#define _ARP_H
#include <pcap.h>
#include <main.h>
#include <stdint.h>

// Constants
#define PROMISCUOUS 1

#define ETHERTYPE_IP 0x8000
#define ETHERTYPE_ARP 0x0806

#define ARP_HW_TYPE 0x0001
#define ARP_PROTO_TYPE 0x0800
#define ARP_HW_LEN 0x06
#define ARP_PROTO_LEN 0x04
#define ARP_OPCODE 0x0001

typedef struct _ArpSession {
	MacManager senderMacAddress;
	IpManager senderIpAddress;
	MacManager targetMacAddress;
	IpManager targetIpAddress;
} ArpSession;

#pragma pack(push, 1)
typedef struct _EthernetHeader {
	MacManager destinationMacAddress;
	MacManager sourceMacAddress;
	uint16_t type;
} EthernetHeader;

typedef struct _ArpHeader {
	uint16_t hardwareType;
	uint16_t protocolType;
	uint8_t hardwareLength;
	uint8_t protocolLength;
	uint16_t opcode;
	MacManager senderHardwareAddress;
	IpManager senderProtocolAddress;
	MacManager targetHardwareAddress;
	IpManager targetProtocolAddress;
} ArpHeader;

typedef struct _MergedHeader {
	EthernetHeader ethernetPacket;
	ArpHeader arpPacket;
} MergedHeader;
#pragma pack(pop)

int receiveSenderMacAddress(IN pcap_t *handle, IN IpManager senderIpAddress, OUT MacManager &senderMacAddress);
int getSenderMacAddress(IN pcap_t *handle, IN MacManager targetMacAddress, IN IpManager targetIpAddress, IN IpManager senderIpAddress, OUT MacManager &senderMacAddress);
int infectSender(IN pcap_t *handle, IN MacManager localMacAddress, IN ArpSession arpSession, IN int count);

#endif
