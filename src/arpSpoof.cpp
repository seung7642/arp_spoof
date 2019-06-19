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

int
ArpSpoof::setSenderMacAddress()
{
	// getting Sender MAC Address through ioctl().
	struct ifreq ifr;
	
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	strncpy(ifr.ifr_name, this->interface, IFNAMSIZ - 1);

	if (ioctl(sock, SIOCGIFCONF, &ifr)) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}

	memset(this->senderMacAddress, ifr.ifr_hwaddr.sa_data, 6);

	close(sock);
	return 0;
}

u_char*
ArpSpoof::setTargetMacAddress(pcap_t* handle, u_char& senderIpAddress, u_char& senderMacAddress, u_char& targetIpAddress, u_char& targetMacAddress) 
{
	// getting MAC Address through Broadcasting.
	
	

	return mac;	
}

int
ArpSpoof::setArpHeader(char& senderIpAddress, char& targetIpAddress)
{
	memset(this->arpHdr.senderHardwareAddress, this->senderMacAddress, 6);
	memset(this->arpHdr.targetHardwareAddress, this->targetMacAddress, 6);
	memset(this->arpHdr.senderProtocolAddress, senderIpAddress, 4);
	memset(this->arpHdr.targetProtocolAddress, targetIpAddress, 4);

	this->arpHdr.hardwareType = htons(ARP_HW_TYPE);
	this->arpHdr.protocolType = htons(ARP_PROTO_TYPE);
	this->arpHdr.hardwareLength = ARP_HW_LEN;
	this->arpHdr.protocolLength = ARP_PROTO_LEN;
	this->arpHdr.opcode = htons(ARP_OPCODE);
}

int
ArpSpoof::setEtherHeader()
{
	memset(this->etherHdr.destinationMacAddress, this->targetMacAddress, 6);
	memset(this->etherHdr.sourceMacAddress, this->senderMacAddress, 6);
	this->etherHdr.type = htons(ETHERTYPE_ARP);
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
