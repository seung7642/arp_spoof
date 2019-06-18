#include "main.h"
#include "arp.h"
#include "ethernet.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

// Print Usage
void
usage()
{
	printf("Usage: arp_spoof <interface> <sender ip> <target ip>\n");
	printf("sample: arp_spoof wlan0 10.0.0.1 10.0.0.2\n");
}

int
main(int argc, char* argv[])
{

	return 0;
}
