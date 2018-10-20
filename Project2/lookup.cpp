
#include "headers.h"
#include "lookup.h"

Question::Question(void)  // constructor
{

};

// Packet visual:
// [ DNS Header - Question Buffer - Query Header ]
bool Question::MakePacket(u_char* pkt, FixedDNSheader &dnsheader, QueryHeader &queryheader)
{
	int hdr_size = sizeof(FixedDNSheader);
	int buf_size = sizeof(rawbuffer);

	// add the dns header to pkt
	memcpy(pkt, &dnsheader, hdr_size);

	// copy the mem from rawbuffer to pkt
	memcpy(pkt + hdr_size, rawbuffer, sizeof(rawbuffer));

	// add the query header to pkt
	memcpy(pkt + hdr_size + buf_size, &queryheader, hdr_size);

	return true;

}

bool Question::CreateQuestion(string host)
{
	rawbuffer = new u_char[
		sizeof(FixedDNSheader) + sizeof(QueryHeader) + host.size() + 2];

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

	return true;
}
