#include "arpSpoof.h"

ArpSpoof::ArpSpoof(u_char& iface) : interface{ iface }, arpHdr{ 0 }, etherHdr{ 0 }
{
	memset(senderMacAddress, 0x00, 6);
	memset(targetMacAddress, 0xFF, 6);
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

int
ArpSpoof::setTargetMacAddress(pcap_t* handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress) 
{
	// getting MAC Address through Broadcasting.
	uint8_t packet[sizeof(etherHeader) + sizeof(arpHeader)];

	setEtherHeader();
	setArpHeader(senderIpAddress, targetIpAddress);

	memcpy(packet, this->ethHdr, sizeof(etherHeader));
	memcpy(packet + sizeof(etherHeader), this->arpHdr, sizeof(arpHeader));
	
	while (1) {
		cout << "[*] Broadcasting for getting Target MAC Address" << endl;
		if (pcap_sendpacket(handle, packet, sizeof(packet))) {
			perror("pcap_sendpacket");
			exit(EXIT_FAILURE);
		}
		sleep(1);

		if (receiveTargetMacAddress()) {
			break;
		}
	}

	return 0;	
}

int
ArpSpoof::setArpHeader(uint8_t& senderIpAddress, uint8_t& targetIpAddress)
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
ArpSpoof::sendInfectPacket(IN pcap_t* handle, IN uint8_t* senderIpAddress, IN uint8_t* targetIpAddress)
{
	uint8_t* senderMacAddress;
	uint8_t packet[sizeof(etherHeader) + sizeof(arpHeader)];
	etherHeader* ethernetPacket;
	arpHeader* arpPacket;

	senderMacAddress = getSenderMacAddress(interface);

	return 0;
}

int
ArpSpoof::receivePacketRelay(pcap_t* handle, uint8_t* senderIpAddress, uint8_t* targetIpAddress)
{
	struct pcap_pkthdr* pcapHeader;
	uint8_t* packet;

	if (pcap_next_ex(handle, &pcapHeader, &packet)) {
		perror("pcap_next_ex");
		exit(EXIT_FAILURE);
	}

	etherHeader* ether = (etherHeader*)packet;

	switch (ntohs(ether->type)) {
	case ETHERTYPE_ARP:

	default:
		break;
	}
}
