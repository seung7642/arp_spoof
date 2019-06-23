#include "arpSpoof.h"

ArpSpoof::ArpSpoof(uint8_t& iface) : interface(iface) {
}

int ArpSpoof::sendInfectPacket(pcap_t& handle, uint8_t& senderIp, uint8_t& targetIp) {

	return 0;
}

int ArpSpoof::receivePacketRelay(pcap_t& handle) {
	// TODO: packet parsing 

	return 0;
}
