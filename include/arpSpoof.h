class ArpSpoof
{
private:
	uint8_t* interface;
	arpHeader arpHdr;
	etherHeader etherHdr;
	uint8_t senderMacAddress[6];
	uint8_t targetMacAddress[6];

public:
	ArpSpoof(u_char& interface, arpHeader arp, etherHeader ether);

	int setSenderMacAddress();
	int setTargetMacAddress();
	int setArpHeader(char& senderIpAddress, char& targetIpAddress);
	int setEtherHeader();
	int sendInfectPacket(pcap_t& handle, char& senderIpAddress, char& targetIpAddress);
	int receivePacketRelay();
}
