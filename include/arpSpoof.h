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
	uint8_t& interface;
	Arp arp;
	Ethernet ethernet;
	uint8_t* senderMacAddress;
	uint8_t* targetMacAddress;

public:
	ArpSpoof(uint8_t& interface);

	int setSenderMacAddress();
	int setTargetMacAddress(pcap_t& handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress);
	int sendInfectPacket(pcap_t& handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress);
	int receivePacketRelay(pcap_t& handle);
};
#pragma pack(pop)

#endif
