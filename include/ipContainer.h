#ifndef _IP_CONTAINER_H
#define _IP_CONTAINER_H

#include <iostream>
#include <cstring>
using namespace std;

#pragma pack(push, 1)
class ipContainer {
private:
	uint8_t ipAddress[4];

public:
	ipContainer() {};
	ipContainer(uint8_t& ip);

	void printIpAddress() const;

	ostream& operator<<(const ipContainer& ip) {
		int cnt = 3;
		for (auto ip : ip.ipAddress) {
			cout << ip;
			if (cnt--) cout << ".";
		}
	}
};
#pragma pack(pop)

#endif
