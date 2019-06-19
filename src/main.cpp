#include "main.h"
#include "arpSpoof.h"

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

	// do ARP Spoofing ...
	arp.setEtherHeader();
	arp.setArpHeader();
	arp.sendInfectPacket();

	arp.receivePacketRelay();


	if (handle) pcap_close(handle);

	return 0;
}
