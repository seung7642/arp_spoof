#include "main.h"
#include "arp.h"

// Print Usage
void usage() {
	printf("Usage: arp_spoof <interface> <sender ip> <target ip>\n");
	printf("sample: arp_spoof wlan0 192.168.0.1 192.168.0.2\n");
}

int main(int argc, char* argv[]) {
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];

	uint8_t localMacAddress[6];
	uint8_t localIpAddress[4];

	uint8_t senderMacAddress[6];
	uint8_t senderIpAddress[4];
	uint8_t targetMacAddress[6];
	uint8_t targetIpAddress[4];

	if (argc != 4) {
		usage();
		exit(EXIT_FAILURE);
	}

	inet_pton(AF_INET, argv[2], senderIpAddress);
	inet_pton(AF_INET, argv[3], targetIpAddress);

	handle = pcap_open_live(argv[1], BUFSIZ, PROMISCUOUS, 1024, errbuf);
	if (handle == NULL) {
		perror("pcap_open_live");
		exit(EXIT_FAILURE);
	}

	// 1. getting me and target MAC Address
	if (getLocalMacAddress(argv[1], localMacAddress)) {
		fprintf(stderr, "failed getLocalMacAddress()\n");
		exit(EXIT_FAILURE);
	}
	if (getLocalIpAddress(argv[1], localIpAddress)) {
		fprintf(stderr, "failed getLocalIpAddress()\n");
		exit(EXIT_FAILURE);
	}
	getMacAddress(handle, localIpAddress, localMacAddress, senderIpAddress, senderMacAddress);
	getMacAddress(handle, localIpAddress, localMacAddress, targetIpAddress, targetMacAddress);
	

	// 2. send ARP Packet to target for infect 

	// 3. if receive packet of target, relay packet to target. 

	if (handle) pcap_close(handle);

	return 0;
}
