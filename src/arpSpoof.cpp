#include "arpSpoof.h"

ArpSpoof::ArpSpoof(u_char& iface) : interface{ iface }, arpHdr{ 0 }, etherHdr{ 0 }
{
	memset(senderMacAddress, 0x00, 6);
	memset(targetMacAddress, 0x00, 6);
}

ArpSpoof::~ArpSpoof()
{
	// do nothing
}

u_char*
ArpSpoof::getMacAddress(u_char* ip) 
{
	// getting MAC Address through Broadcasting.
	
	
	return mac;	
}

int
ArpSpoof::setArpHeader(u_char& senderMacAddress, char& sendIp, char& targetIp, arpHeader arp)
{

}

int
ArpSpoof::setEtherHeader(u_char& senderMacAddress, etherHeader eth)
{

}
	
int
ArpSpoof::sendInfectPacket(IN pcap_t* handle, IN char* senderIpAddress, IN char* targetIpAddress)
{
	u_char* senderMacAddress;
	uint8_t packet[sizeof(etherHeader) + sizeof(arpHeader)];
	etherHeader* ethernetPacket;
	arpHeader* arpPacket;

	senderMacAddress = getSenderMacAddress(interface);

	return 0;
}

int
ArpSpoof::receivePacketRelay()
{

}
