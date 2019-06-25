#include "arp.h"

int getLocalMacAddress(char* interfaceName, OUT uint8_t* localMacAddress) {
	struct ifreq interfaceRequest;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	strncpy(interfaceRequest.ifr_name, interfaceName, IFNAMSIZ - 1);

	if (ioctl(sock, SIOCGIFHWADDR, &interfaceRequest)) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}

	localMacAddress = (uint8_t*)interfaceRequest.ifr_hwaddr.sa_data;

	if (sock) close(sock);
	return 0;
}

int getLocalIpAddress(char* interfaceName, OUT uint8_t* localIpAddress) {
	struct ifreq interfaceRequest;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	strncpy(interfaceRequest.ifr_name, interfaceName, IFNAMSIZ - 1);

	if (ioctl(sock, SIOCGIFADDR, &interfaceRequest)) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}

	localIpAddress = (uint8_t*)interfaceRequest.ifr_addr.sa_data;

	if (sock) close(sock);
	return 0;
}

int getMacAddress(IN pcap_t* handle, IN uint8_t* localIpAddress, IN uint8_t* localMacAddress, IN uint8_t* targetIpAddress, OUT uint8_t* targetMacAddress) {
	uint8_t packet[sizeof(EtherHeader) + sizeof(ArpHeader)];
	EtherHeader* ether;
	ArpHeader* arp;

	memset(ether->destinationMacAddress, 0xFF, 6);
	memcpy(ether->sourceMacAddress, localMacAddress, 6);
	ether->type = ETHERTYPE_ARP;

	arp->hardwareType = ARP_HW_TYPE;
	arp->protocolType = ARP_PROTO_TYPE;
	arp->hardwareLength = ARP_HW_LEN;
	arp->protocolLength = ARP_PROTO_LEN;
	arp->opcode = ARP_OPCODE;
	memcpy(arp->senderHardwareAddress, localMacAddress, 6);
	memcpy(arp->senderProtocolAddress, localIpAddress, 4);
	memset(arp->targetHardwareAddress, 0xFF, 6);
	memcpy(arp->targetProtocolAddress, targetIpAddress, 4);

	// setting packet for broadcasting
	memcpy(packet, ether, sizeof(EtherHeader));
	memcpy(packet + sizeof(EtherHeader), arp, sizeof(ArpHeader));

	while (1) {
		printf("[*] Broadcasting for getting Target MAC Address\n");
		if (pcap_sendpacket(handle, packet, sizeof(packet))) {
			perror("pcap_sendpacket");
			exit(EXIT_FAILURE);
		}
		sleep(1);

		printf("[*] Get MAC Address\n");
		if (receiveMacAddress(handle, localIpAddress, localMacAddress, targetIpAddress, targetMacAddress)) {
			break;
		}
	}

	return 0;
}

int receiveMacAddress(IN pcap_t* handle, IN uint8_t* localIpAddress, IN uint8_t* localMacAddress, IN uint8_t* targetIpAddress, OUT uint8_t* targetMacAddress) {
	struct pcap_pkthdr* pcapHeader;
	const uint8_t* packet;

	if (pcap_next_ex(handle, &pcapHeader, &packet)) {
		perror("pcap_next_ex");
		exit(EXIT_FAILURE);
	}

	EtherHeader* ether = (EtherHeader*)(packet);
	ArpHeader* arp = (ArpHeader*)(packet + 14);

	switch (ntohs(ether->type)) {
	case ETHERTYPE_ARP:
		if (!memcmp(arp->senderProtocolAddress,targetIpAddress, 4) 
				&& !memcmp(arp->targetHardwareAddress, localMacAddress, 6) 
				&& !memcmp(arp->targetProtocolAddress, localIpAddress, 4)) {
			memcpy(targetMacAddress, arp->senderHardwareAddress, 6);
			return 1;
		}
		break;

	default:
		break;
	}

	return 0;
}

int infectSender(pcap_t* handle, uint8_t* localMacAddress, ArpSession arpSession) {

}
