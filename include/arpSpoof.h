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

public:
	ArpSpoof(uint8_t& interface);

	int sendInfectPacket(pcap_t& handle, uint8_t& senderIp, uint8_t& targetIp);
	int receivePacketRelay(pcap_t& handle);
};
#pragma pack(pop)

#endif
