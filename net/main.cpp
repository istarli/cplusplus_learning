#include "packet.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	ether_header ethhdr;
	cout << sizeof(ethhdr) << endl;
	arp_header head;
	cout << sizeof(head) << endl;
	arp_payload pld;
	cout << sizeof(pld) << endl;
	arp_packet pkt;
	cout << sizeof(pkt) << endl;	
	return 0;
}