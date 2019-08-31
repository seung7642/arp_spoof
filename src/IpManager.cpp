#include <stdio.h>
#include <string.h>
#include <ostream>
#include <IpManager.h>
#include <arpa/inet.h>

// 생성자
IpManager::IpManager(IN uint8_t* ipAddress) {
    memcpy(this->ipAddress, ipAddress, LENGTH);
}

IpManager::IpManager(IN char* ipAddressString) {
    struct in_addr laddr;
    if (inet_aton(ipAddressString, &laddr) < 0) {
        fprintf(stderr, "[-] IP Address Format Invalid!\n");
    } else {
        memcpy(this->ipAddress, &laddr.s_addr, LENGTH);
    }
}

IpManager::IpManager(IN struct in_addr laddr) {
    memcpy(ipAddress, &laddr.s_addr, LENGTH);
}

void IpManager::printIpAddress(IN const char *prefix, IN uint8_t *ipAddress) {
    printf("%s[%d.%d.%d.%d]\n", prefix, ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
}

void IpManager::printIpAddress(IN const char *prefix) {
    printf("%s[%d.%d.%d.%d]\n", prefix, ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
}