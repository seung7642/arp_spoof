#include "main.h"
#include "arpSpoof.h"

int getSenderMacAddress(char* interface, OUT uint8_t* senderMac) {
	// getting sender MAC Address through ioctl().
	struct ifreq ifr;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memcpy(ifr.ifr_name, interface, IFNAMSIZ - 1);

	if (ioctl(sock, SIOCGIFCONF, &ifr)) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}

	senderMac = (uint8_t*)ifr.ifr_hwaddr.sa_data;

	close(sock);
	return 0;
}

int getTargetMacAddress(pcap_t* handle, char* senderIp, char* targetIp, uint8_t* senderMac, OUT uint8_t* targetMac) {
	// getting MAC Address through broadcasting.
	uint8_t packet[sizeof(etherHeader) + sizeof(arpHeader)];
	etherHeader* ether;
	arpHeader* arp;

	memset(ether->destinationMacAddress, 0xFF, 6);
	memcpy(ether->sourceMacAddress, senderMac, 6);
	ether->type = ETHERTYPE_ARP;

	arp->hardwareType = ARP_HW_TYPE;
	arp->protocolType = ARP_PROTO_TYPE;
	arp->hardwareLength = ARP_HW_LEN;
	arp->protocolLength = ARP_PROTO_LEN;
	arp->opcode = ARP_OPCODE;
	memcpy(arp->senderHardwareAddress, senderMac, 6);
	memcpy(arp->senderProtocolAddress, senderIp, 4);
	memset(arp->targetHardwareAddress, 0xFF, 6);
	memcpy(arp->targetProtocolAddress, targetIp, 4);

	// setting packet for broadcasting
	memcpy(packet, ether, sizeof(etherHeader));
	memcpy(packet + sizeof(etherHeader), arp, sizeof(arpHeader));

	while (1) {
		printf("[*] Broadcasting for getting Target MAC Address\n");
		if (pcap_sendpacket(handle, packet, sizeof(packet))) {
			perror("pcap_sendpacket");
			exit(EXIT_FAILURE);
		}
		sleep(1);

		if (packetParsing(handle, senderIp, targetIp, targetMac)) {
			break;
		}
	}

	return 0;
}

int packetParsing(pcap_t* handle, char* senderIp, char* targetIp, OUT uint8_t* targetMac) {
	struct pcap_pkthdr* pcapHeader;
	const uint8_t* packet;

	if (pcap_next_ex(handle, &pcapHeader, &packet)) {
		perror("pcap_next_ex");
		exit(EXIT_FAILURE);
	}

	etherHeader* ether = (etherHeader*)(packet);
	arpHeader* arp = (arpHeader*)(packet + 14);

	switch (ntohs(ether->type)) {
	case ETHERTYPE_ARP:
		if (!memcmp(arp->senderProtocolAddress,targetIp, 4)) {
			memcpy(targetMac, arp->senderHardwareAddress, 6);
			return 1;
		}
		break;

	default:
		break;
	}

	return 0;
}

// Print Usage
void usage() {
	cout << "Usage: arp_spoof <interface> <sender ip> <target ip>" << endl;
	cout << "sample: arp_spoof wlan0 10.0.0.1 10.0.0.2" << endl;
}

int main(int argc, char* argv[]) {
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	uint8_t senderMacAddress[6];
	uint8_t targetMacAddress[6];

	if (argc != 4) {
		usage();
		exit(EXIT_FAILURE);
	}

	handle = pcap_open_live(argv[1], BUFSIZ, PROMISCUOUS, 1024, errbuf);
	if (handle == NULL) {
		perror("pcap_open_live");
		exit(EXIT_FAILURE);
	}

	// 1. getting me and target MAC Address
	if (getSenderMacAddress(argv[1], senderMacAddress)) {
		fprintf(stderr, "failed getSenderMacAddress()\n");
		exit(EXIT_FAILURE);
	}

	if (getTargetMacAddress(handle, argv[2], argv[3], senderMacAddress, targetMacAddress)) {
		fprintf(stderr, "failed getTargetMacAddress()\n");
		exit(EXIT_FAILURE);
	}
	
	ArpSpoof arpSpoof{ argv[1], argv[2], argv[3], senderMacAddress, targetMacAddress };

	// 2. send ARP Packet to target for infect 

	// 3. if receive packet of target, relay packet to target. 

	if (handle) pcap_close(handle);

	return 0;
}
