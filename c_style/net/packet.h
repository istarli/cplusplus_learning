#ifndef __PACKET_H__
#define __PACKET_H__

#define Int8 unsigned char 
#define Int16 unsigned short 
#define Int32 unsigned int 
#define Int64 unsigned long 

struct vlan_tag {
	Int16 vlantype; // 0x8100
	// 3bit(priority)+1bit(CFI)+12bit(vid)
	// max_vid = 2^12-1 = 4095
	Int16 pri_CFI_vid;
};

/* Media Access Control*/
struct ether_header {
	Int8 ether_dst[6];
	Int8 ether_src[6];
	/* vlan_tag vlan; */
	Int16 type;
};

enum ether_protocols {
	IP = 0x0800,
	ARP = 0x0806,
	VLAN = 0x8100,
};

struct ether_tail {
	// Frame check sequence.
	// The way to check may be CRC(Circle Redundancy Check).
	Int32 fcs;
};

// max length of an ether_frame : 
//      1500(MTU)+18(no vlan) = 1518 Bytes,
//		1500(MTU)+18+4(vlan) = 1522 Bytes.
struct ether_frame {
	ether_header head;
	ether_tail tail;
	Int8 payload[0]; // 46~1500B,MTU
};

/* Address Resolution Protocol*/
struct arp_header {
	Int16 arp_hrd; /* format of hardware address, ether_addr=0x0001 */
	Int16 arp_pro; /* format of protocol address, ip_addr=0x0800 */
	Int8 arp_hln; /* length of hardware address, 6 */
	Int8 arp_pln; /* length of hardware address, 4*/
	Int16 arp_op; /* ARP/RARP operation,  */
};

enum arp_oprations {
	ARP_REQUEST = 0x0001,
	ARP_REPLY = 0x0002,
};

struct arp_payload {
	Int8 arp_sha[6]; /* sender hardware address */
	Int8 arp_spa[4]; /* sender protocol address */
	Int8 arp_tha[6]; /* target hardware address */
	Int8 arp_tpa[4]; /* target protocol address */
};

struct arp_message {
	arp_header head;
	arp_payload payload;
};

/* Size is 42 bytes */
struct arp_packet {
	ether_header ehhdr;
	arp_message arpmsg;
};

struct ip_header {
	/*********row 1************/
	// 4bit(version)+4bit(header_length)
	// min_hl = 20B = 5(int) = 0101
	// max_hl = 2^4-1 = 15(int) = 60B
	// so max_optons_len = 60-20 = 40B
	Int8 v_hl; 
	Int8 tos;
	// Attention: the uInt32 of total length is Byte, not int.
	// max_len = 2^16-1 = 65535B.
	// Due to MTU=1500, length = 1500-20 = 1480 is enough.
	Int16 len;
	/*********row 2************/
	// Identification for IP-Message, 2B, 0~65535.
	// Recombine those fragments with the same ide.
	Int16 ide;
	// 1(reserve)+2(MF,DF)+13(offset)
	// MF=1 means More-Fragment, DF=1 means Don't-Fragment.
	// Offset means the position of fragment in origin message.(8B) 
	Int16 flags_offset;
	/*********row 3************/
	Int8 ttl;
	Int8 proto;
	// Not CRC, but simply used one's-complement-sum.
	Int16 checksum;
	/*********row 4************/
	Int32 ip_src;
	/*********row 5************/
	Int32 ip_dst;
	/*********row n************/
	Int8 options[0];
};

enum ip_protocols {
	ICMP = 1, // ICMP
	IGMP = 2,
	IPv4 = 4, // IPv4
	TCP = 6, // TCP
	EGP = 8,
	IGP = 9,
	UDP = 17, // UDP
	IPv6 = 41, // IPv6
	GRE = 47,
	ESP = 50,
	OSPF = 89, // OSPF
};

struct ip_message {
	ip_header head;
	Int8 payload[0];
};

/* Total 24 bytes */
struct ospf_header {
	/*********row 1***********/
	Int8 ver;
	Int8 type;
	Int16 len;
	/*********row 2***********/
	Int32 route_ide;
	/*********row 3***********/
	Int32 area_ide;
	/*********row 4***********/
	Int16 checksum;
	Int16 identify_type;
	/*********row 5***********/
	Int32 identify_data1;
	/*********row 6***********/
	Int32 identify_data2;
};

enum ospf_type {
	Hello = 1,
	DatabaseDescription = 2,
	LinkStateRequest = 3,
	LinkStateUpdate = 4,
	LinkStateAcknowledgment = 5,
};

struct udp_header {
	/*********row 1************/
	Int16 port_src;
	Int16 port_dst;
	/*********row 2************/
	Int16 len;
	Int16 checksum;
};

enum udp_ports {
	SMTP = 25,
	DNS = 53,
	DHCP_CLIENT = 67,
	DHCP_SERVER = 68,
	SNMP = 161,
	RIP = 520,
};

struct  udp_message {
	udp_header head;
	Int8 payload[0];
};

struct tcp_header {
	/*********row 1************/
	Int16 port_src;
	Int16 port_dst;
	/*********row 2************/
	Int32 seq_no; // every byte has a seq_no
	/*********row 3************/
	Int32 ack_no;
	/*********row 4************/
	// 4(offset)+6(reserve)+6(URG,ACK,PSH,RST,SYN,FIN)
	// Actually, offset equals to head_length.
	// The max head lengh is 2^4-1 = 15(int) = 60B.
	// So the max options length is 60-20=40B.
	Int16 offset_flags; 
	Int16 window;
	/*********row 5************/
	Int16 checksum;
	Int16 urg_ptr;
	/*********row n************/
	Int8 options[0];
};

struct tcp_message {
	tcp_header head;
	Int8 payload[0];
};

enum tcp_ports {
	FTP = 21,
	TELNET = 23,
	SMTP = 25,
	HTTP = 80,
};

#endif