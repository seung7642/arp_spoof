#ifndef _ARP_H
#define _ARP_H

#include <iostream>
#include <cstring>
using namespace std;

#pragma pack(push, 1)
class Arp {
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

	// constants
	static constexpr uint16_t HW_TYPE = 0x0001;
	static constexpr uint16_t PROTO_TYPE = 0x0800;
	static constexpr uint8_t HW_LEN = 0x06;
	static constexpr uint8_t PROTO_LEN = 0x04;
	static constexpr uint16_t OPCODE = 0x0001;

public:
	Arp() {};
	Arp(uint8_t& senderHw, uint8_t& senderIp, uint8_t& targetHw, uint8_t& targetIp);

	int setInfo(uint8_t& senderHw, uint8_t& senderIp, uint8_t& targetHw, uint8_t& targetIp);

	ostream& operator<<(Arp& arp);
};
#pragma pack(pop)

#endif
