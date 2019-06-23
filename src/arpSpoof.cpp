#include "arpSpoof.h"

ArpSpoof::ArpSpoof(char* iface, char* senderIp, char* targetIp, uint8_t* senderMac, uint8_t* targetMac) : interface{ iface } {
	memcpy(senderIpAddress, senderIp, 4);
	memcpy(targetIpAddress, targetIp, 4);
	memcpy(senderMacAddress, senderMac, 6);
	memcpy(targetMacAddress, targetMac, 6);
}

int ArpSpoof::sendInfectPacket(pcap_t* handle, char* senderIp, char* targetIp) {
	uint8_t packet[sizeof(etherHeader) + sizeof(arpHeader)];

	// 1. setting packet
	
	
	// 2. send packet of infect
	int cnt = 10;
	while (cnt) {
		cout << "[*] Send Packet of Infect" << endl;
		if (pcap_sendpacket(handle, packet, sizeof(packet))) {
			perror("pcap_sendpacket");
			exit(EXIT_FAILURE);
		}
		sleep(1);
		cnt--;
	}

	return 0;
}

int ArpSpoof::receivePacketRelay(pcap_t* handle) {
	struct pcap_pkthdr* pcapHeader;
	const uint8_t* packet;

	while (1) {
		if (pcap_next_ex(handle, &pcapHeader, &packet)) {
			perror("pcap_next_ex");
			exit(EXIT_FAILURE);
		}
		
		// How to judge packet of target?
		etherHeader* ether = (etherHeader*)(packet);
		arpHeader* arp = (arpHeader*)(packet + 14);
	}

	return 0;
}
