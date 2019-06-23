#include "ipContainer.h"

ipContainer::ipContainer(uint8_t& ip) {
	memset(ipAddress, ip, 4);
}

void ipContainer::printIpAddress() const {
	// TODO: printting
}


