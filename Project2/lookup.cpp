#include "headers.h"
#include "lookup.h"

Question::Question(void)  // constructor
{

};

bool Question::MakePacket(u_char* pkt, FixedDNSheader &dnsheader, QueryHeader &queryheader)
{

	return true;

}

bool Question::CreateQuestion(string host) {

	//+1 byte for "size" for last substring, +1 for "0" meaning the end of question
	//int pkt_size = sizeof(FixedDNSheader) + sizeof(QueryHeader) + host.size() + 2;

	//char* pkt = new char[pkt_size];
	int position = host.find(".");
	string sub_str;

	int i = 0, sub_size = 0, hdr_size = sizeof(FixedDNSheader);

	// parse the host and place contents in packet
	host += ".";
	while (position != -1)
	{
		sub_size = position - i;
		sub_str = host.substr(i, position);

		rawbuffer[hdr_size + i] = sub_size;  // specify the size of the chunk (subdomain)
		i++;
		memcpy(rawbuffer + hdr_size + i, sub_str.c_str(), sub_size); // specify the actual subdomain

		i += sub_size;
		position = host.find(".", i);
	}
	rawbuffer[hdr_size + i] = 0;

	// add the query type and query class to the end of packet
	//pkt[hdr_size + i + 1] = DNS_PTR;
	//pkt[hdr_size + i + 2] = DNS_INET;

	return true;
}
