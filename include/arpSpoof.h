#ifndef _ARP_SPOOF_H
#define _ARP_SPOOF_H
#include "main.h"

class ArpSpoof
{
private:
	uint8_t& interface;
	arpHeader arpHdr;
	etherHeader etherHdr;
	uint8_t senderMacAddress[6];
	uint8_t targetMacAddress[6];

public:
	ArpSpoof(uint8_t& interface);

	int setSenderMacAddress();
	int setTargetMacAddress(pcap_t& handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress);
	int setArpHeader(uint8_t& senderIpAddress, uint8_t& targetIpAddress);
	int setEtherHeader();
	int sendInfectPacket(pcap_t& handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress);
	int receivePacketRelay();
};

#endif
