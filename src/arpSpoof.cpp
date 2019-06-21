#include "arpSpoof.h"

ArpSpoof::ArpSpoof(uint8_t& iface) : interface(iface) {
	memset(senderMacAddress, 0x00, 6);
	memset(targetMacAddress, 0xFF, 6);
}

int ArpSpoof::setSenderMacAddress() {
	// getting Sender MAC Address through ioctl().
	struct ifreq ifr;
	
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	strncpy(ifr.ifr_name, const_cast<char*>(this->interface), IFNAMSIZ - 1);

	if (ioctl(sock, SIOCGIFCONF, &ifr)) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}

	memset(this->senderMacAddress, (uint8_t)ifr.ifr_hwaddr.sa_data, 6);

	close(sock);
	return 0;
}

int ArpSpoof::setTargetMacAddress(pcap_t& handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress) {
	// getting MAC Address through Broadcasting.
	uint8_t packet[sizeof(etherHeader) + sizeof(arpHeader)];

	setEtherHeader();
	setArpHeader(senderIpAddress, targetIpAddress);

	memcpy(packet, this->etherHdr, sizeof(etherHeader));
	memcpy(packet + sizeof(etherHeader), this->arpHdr, sizeof(arpHeader));
	
	while (1) {
		cout << "[*] Broadcasting for getting Target MAC Address" << endl;
		if (pcap_sendpacket(handle, packet, sizeof(packet))) {
			perror("pcap_sendpacket");
			exit(EXIT_FAILURE);
		}
		sleep(1);

		// if getting Target MAC Address...
		if (receiveTargetMacAddress()) {
			break;
		}
	}

	return 0;	
}

int ArpSpoof::receiveTargetMacAddress(pcap_t& handle, uint8_t& senderIpAddress, uint8_t& targetIpAddress)
{
	struct pcap_pkthdr* pcapHeader;
	uint8_t* packet;

	if(pcap_next_ex(handle, &pcapHeader, packet)) {
		perror("pcap_next_ex");
		exit(EXIT_FAILURE);
	}

	etherHeader* ether = (etherHeader*)(packet);
	arpHeader* arp = (arpHeader*)(packet + 14);

	switch (ntohs(ether->type)) {
	case ETHERTYPE_ARP:


	default:
		break;
	}
}

int ArpSpoof::sendInfectPacket(IN pcap_t& handle, IN uint8_t& senderIpAddress, IN uint8_t& targetIpAddress) {

	return 0;
}

int ArpSpoof::receivePacketRelay(pcap_t& handle) {

	return 0;
}
