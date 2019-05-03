class Arp
{
	public:
		explicit Arp();
		~Arp();
		int setArpPacket();

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
}
