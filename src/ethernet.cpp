#include "ethernet.h"

Ethernet::Ethernet(uint8_t& destinationMac, uint8_t& sourceMac) {
	memset(destinationMacAddress, destinationMac, 6);
	memset(sourceMacAddress, sourceMac, 6);
	type = TYPE_ARP;
}

int Ethernet::setInfo(uint8_t& destinationMac, uint8_t& sourceMac) {
	memset(destinationMacAddress, destinationMac, 6);
	memset(sourceMacAddress, sourceMac, 6);
}

ostream& Ethernet::operator<<(Ethernet& ethernet) {
	// TODO: How to formatting...
}
