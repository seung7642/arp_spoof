class ArpSpoof
{
	public:
		// method
		ArpSpoof(arpHeader arp, etherHeader ether);
		~ArpSpoof();
		u_char* getSenderMacAddress(u_char& interface);
		int setArpHeader(u_char& senderMacAddress, char& sendIp, char& targetIp, arpHeader& arp);
		int setEthHeader(u_char& senderMacAddress, etherHeader& eth);
		int sendArpPacket(pcap_t& handle, char& interface, char& senderIpAddress, char& targetIpAddress);
		int redirectPacket();

	private:
		arpHeader arpHdr;
		etherHeader etherHdr;
}
