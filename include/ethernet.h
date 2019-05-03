class Ethernet
{
	public:
		Ethernet();
		~Ethernet();
		setEtherHeader();

	private:
		uint8_t destinationMacAddress[6];
		uint8_t sourceMacAddress[6];
		uint16_t type;

		constexpr uint16_t ETHERTYPE_IP{0x8000};
		constexpr uint16_t ETHERTYPE_ARP{0x0806};
}
