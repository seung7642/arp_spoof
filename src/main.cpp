#include <main.h>
#include <util.h>
#include <arp.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

// Print Usage
void usage() {
	printf("Usage: arp_spoof <interface> <sender ip> <target ip>\n");
	printf("sample: arp_spoof wlan0 192.168.0.1 192.168.0.2\n");
}

int main(int argc, char* argv[]) {
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (argc != 4) {
		usage();
		return EXIT_FAILURE;
	}

	handle = pcap_open_live(argv[1], BUFSIZ, PROMISCUOUS, 1024, errbuf);
	if (handle == NULL) {
		perror("pcap_open_live");
		return EXIT_FAILURE;
	}


	if (handle) 
		pcap_close(handle);

	return EXIT_SUCCESS;
}
