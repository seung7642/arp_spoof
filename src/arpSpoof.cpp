#include "arpSpoof.h"

ArpSpoof::ArpSpoof(u_char& iface) : interface{ iface }, arpHdr{ 0 }, etherHdr{ 0 }
{
	// do nothing
}

ArpSpoof::~ArpSpoof()
{
	// do nothing
}

u_char*
ArpSpoof::getSenderMacAddress() 
{
	int fd;
	struct ifreq ifr;
	u_char* mac;
	
	// Create Socket
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, this->interface, IFNAMSIZ - 1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);
	close(fd);

	mac = (u_char*)ifr.ifr_hwaddr.sa_data;
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
