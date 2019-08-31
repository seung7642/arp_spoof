#ifndef _UTIL_H
#define _UTIL_H
#include <arp.h> // arp.h는 main.h를 상속받는다.
#include <main.h>
#include <stdint.h>

int getLocalMacAddress(IN char* interfaceName, OUT MacManager& macManager);
int getLocalIpAddress(IN char* interfaceName, OUT IpManager& ipManager);
void printArpPacketInfo(IN ArpHeader arpPacket);

#endif