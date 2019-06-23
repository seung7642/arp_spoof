#include "arp.h"

Arp::Arp(uint8_t& senderHw, uint8_t& senderIp, uint8_t& targetHw, uint8_t& targetIp) {
	memset(senderHardwareAddress, senderHw, 6);
	memset(senderProtocolAddress, senderIp, 4);
	memset(targetHardwareAddress, targetHw, 6);
	memset(targetProtocolAddress, targetIp, 4);
}

int Arp::setInfo(uint8_t& senderHw, uint8_t& senderIp, uint8_t& targetHw, uint8_t& targetIp) {
	memset(senderHardwareAddress, senderHw, 6);
	memset(senderProtocolAddress, senderIp, 4);
	memset(targetHardwareAddress, targetHw, 6);
	memset(targetProtocolAddress, targetIp, 4);
}

ostream& Arp::operator<<(Arp& arp) {
	// TODO: How to formatting...
	cout << "Sender MAC Address: "
	       	<< senderHardwareAddress[0] << ":"
	       	<< senderHardwareAddress[1] << ":"
		<< senderHardwareAddress[2] << ":"
		<< senderHardwareAddress[3] << endl;

}
