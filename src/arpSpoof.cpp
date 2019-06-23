#include "arpSpoof.h"

ArpSpoof::ArpSpoof(uint8_t& iface) : interface(iface) {
}

int ArpSpoof::sendInfectPacket(IN pcap_t& handle, IN uint8_t& senderIpAddress, IN uint8_t& targetIpAddress) {

	return 0;
}

int ArpSpoof::receivePacketRelay(pcap_t& handle) {
	// TODO: packet parsing 

	return 0;
}
