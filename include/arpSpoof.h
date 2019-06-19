// It has five member field.
class ArpSpoof
{
	public:
		// method
		ArpSpoof(u_char& interface, arpHeader arp, etherHeader ether);
		~ArpSpoof();
		u_char* getMacAddress();
		int setArpHeader(u_char& senderMacAddress, char& sendIp, char& targetIp, arpHeader& arp);
		int setEthHeader(u_char& senderMacAddress, etherHeader& eth);
		int sendInfectPacket(pcap_t& handle, char& interface, char& senderIpAddress, char& targetIpAddress);
		int receivePacketRelay();

	private:
		// member field
		u_char* interface;
		arpHeader arpHdr;
		etherHeader etherHdr;

		u_char senderMacAddress[6];
		u_char targetMacAddress[6];
}
