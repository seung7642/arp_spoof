#include "arp.h"

Arp::Arp(uint8_t& senderHw, uint8_t& senderIp, uint8_t& targetHw, uint8_t& targetIp) {
	memcpy(senderHardwareAddress, senderHw, 6);
	memcpy(senderProtocolAddress, senderIp, 4);
	memcpy(targetHardwareAddress, targetHw, 6);
	memcpy(targetProtocolAddress, targetIp, 4);
}

ostream& Arp::operator<<(ostream& out, const Arp& arp) {
	// TODO: How to formatting...
	cout << "Sender MAC Address: "
	       	<< senderHardwareAddress[0] << ":"
	       	<< senderHardwareAddress[1] << ":"
		<< senderHardwareAddress[2] << ":"
		<< senderHardwareAddress[3] << endl;

}
