#include <arp.h>
#include <util.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// getSenderMacAddress()에서 사용되는 모듈함수
int receiveSenderMacAddress(IN pcap_t *handle, IN IpManager senderIpAddress, OUT MacManager &senderMacAddress) {

}

int getSenderMacAddress(IN pcap_t *handle, IN MacManager targetMacAddress, IN IpManager targetIpAddress, IN IpManager senderIpAddress, OUT MacManager &senderMacAddress) {

}

int infectSender(IN pcap_t *handle, IN MacManager localMacAddress, IN ArpSession arpSession, IN int count) {

}