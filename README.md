# libpcap 라이브러리

### 1. 패킷을 송신하기 위한 함수

```c++
#include <pcap/pcap.h>

int pcap_sendpacket(pcap_t *p, const u_char *buf, int size);
```

**반환값:** 

​    Success : 0

​    Fail : -1

**사용 예)**

```c++
if (pcap_sendpacket(handle, (u_char *)&arpPacket, sizeof(ArpHeader))) {
	fprintf(stderr, “Send Packet Error ! \n”);
	return EXIT_FAILURE;    
}
```



### 2. 패킷을 읽어들이는 함수(패킷 캡처하기 위한 함수)

```c++
#include <pcap/pcap.h>

int pcap_next_ex(pcap_t *p, struct pcap_pkthdr **pkt_header,
        const u_char **pkt_data);
```

패킷을 성공적으로 읽어들였다면, 2번째 매개변수인 pkt_header 포인터는 읽어들인 패킷의 헤더를 가리키고, 3번 째 매개변수인 pkt_data 포인터는 읽어들인 패킷의 데이터 부분을 가리킨다.

**반환 값)**

​    1 : 아무 문제없이 패킷을 읽어들였을 경우

​    0 : live capture로 패킷을 읽어들이는 중에 timeout이 걸린 경우

​    -1 : 패킷을 읽어들이는 도중 에러가 발생한 경우

​    -2 : live capture가 아닌 저장된 파일로부터 패킷을 읽어들이는 경우

**사용 예)**

```c++
struct pcap_pkthdr* pcapHeader;
const u_char* packet;
if (pcap_next_ex(handle, &pcapHeader, &packet) < 0) {
    fprintf(stderr, "Failed receive packet\n");
    return EXIT_FAILURE;
}

// 가져온 패킷을 아래와 같이 형변환으로 옮겨담는다.
EthernetHeader* ethernetPacket = (EthernetHeader *)packet;
```

