#ifndef _IP_CONTAINER_H
#define _IP_CONTAINER_H
#include <stdint.h>

class ipContainer {
private:
	uint8_t ipAddress[4];

public:
	ipContainer() {};
	ipContainer(const uint8_t& ipAddress);

	void printIpAddress();

	ostream& operator<<(ostream& os, const ipContainer& ip) {
		int cnt = 3;
		for (auto ip : ipAddress) {
			cout << ip;
			if (cnt--) cout << ".";
		}
	}
}
#endif
