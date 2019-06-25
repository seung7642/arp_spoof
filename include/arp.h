#ifndef _ARP_H
#define _ARP_H

#include "main.h"

int getLocalMacAddress(char* interfaceName, OUT uint8_t* localMacAddress);
int getLocalIpAddress(char* interfaceName, OUT uint8_t* localIpAddress);
int getMacAddress(IN pcap_t* handle, IN uint8_t* localIpAddress, IN uint8_t* localMacAddress, IN uint8_t* targetIpAddress, OUT uint8_t* targetMacAddress);
int receiveMacAddress(IN pcap_t* handle, IN uint8_t* localIpAddress, IN uint8_t* localMacAddress, IN uint8_t* targetIpAddress, OUT uint8_t* targetMacAddress);

//
int infectSender(pcap_t* handle, uint8_t* localMacAddress, ArpSession arpSession); 

#endif
