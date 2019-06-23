#ifndef _ARP_SPOOF_H
#define _ARP_SPOOF_H

#include <iostream>
#include <cstring>
#include "arp.h"
#include "ethernet.h"
#include "main.h"
using namespace std;

#pragma pack(push, 1)
class ArpSpoof {
private:
	char* interface;
	char senderIpAddress[4];
	char targetIpAddress[4];
	uint8_t senderMacAddress[6];
	uint8_t targetMacAddress[6];
	Arp arp;
	Ethernet ethernet;

public:
	ArpSpoof(char* interface, char* senderIp, char* targetIp, uint8_t* senderMac, uint8_t* targetMac);

	int sendInfectPacket(pcap_t* handle, char* senderIp, char* targetIp);
	int receivePacketRelay(pcap_t* handle);
};
#pragma pack(pop)

#endif
