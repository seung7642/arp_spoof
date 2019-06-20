#include <iostream>

ipContainer::ipContainer(const char& ipAddress) : ipAddress{ ipAddress }
{

}

void
ipContainer::printIpAddress(ipContainer& ip) const
{
	cout << ip << endl;
}


