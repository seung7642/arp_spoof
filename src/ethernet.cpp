#include "ethernet.h"

Ethernet::Ethernet(uint8_t& destinationMac, uint8_t& sourceMac) {
	memcpy(destinationMacAddress, destinationMac, 6);
	memcpy(sourceMacAddress, sourceMac, 6);
	type = ETHERTYPE_ARP;
}

ostream& Ethernet::operator<<(ostream& out, const Ethernet& ethernet) {
	// TODO: How to formatting...
}
