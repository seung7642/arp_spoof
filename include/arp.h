class Arp
{
	public:
		explicit Arp();
		~Arp();
		u_char* getSenderMacAddress(u_char& interface);
		int setArpHeader(u_char& senderMacAddress, char& sendIp, char& targetIp, Arp& arp);
		int sendArpPacket(pcap_t& handle, char& interface, char& senderIpAddress, char& targetIpAddress);
		int redirectPacket();

	private:
		uint16_t hardwareType;
		uint16_t protocolType;
		uint8_t hardwareLength;
		uint8_t protocolLength;
		uint16_t opcode;
		uint8_t senderHardwareAddress[6];
		uint8_t senderProtocolAddress[4];
		uint8_t targetHardwareAddress[6];
		uint8_t targetProtocolAddress[4];

		constexpr uint16_t ARP_HW_TYPE{0x0001};
		constexpr uint16_t ARP_PROTO_TYPE{0x0800};
		constexpr uint8_t ARP_HW_LEN{0x06};
		constexpr uint8_t ARP_PROTO_LEN{0x04};
		constexpr uint16_t ARP_OPCODE{0x0001};
}
