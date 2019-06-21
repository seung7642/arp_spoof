#ifndef _ETHERNET_H
#define _ETHERNET_H

#include <iostream>
#include <cstring>
using namespace std;

#pragma pack(push, 1)
class Ethernet {
private:
	uint8_t destinationMacAddress[6];
	uint8_t sourceMacAddress[6];
	uint16_t type;

	// constants
	static constexpr uint16_t ETHERTYPE_IP = 0x8000;
	static constexpr uint16_t ETHERTYPE_ARP = 0x0806;

public:
	Ethernet() {};
	Ethernet(uint8_t& destinationMac, uint8_t& sourceMac);

	int setInfo(uint8_t& destinationMac, uint8_t& sourceMac);

	friend ostream& operator<<(ostream& out, const Ethernet& ethernet);
};
#pragma pack(pop)

#endif
