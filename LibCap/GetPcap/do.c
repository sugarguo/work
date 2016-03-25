#include <pcap.h>
#include <string.h>
#include <stdlib.h>

#define MAXBYTES2CAPTURE 2048

void processPacket(u_char *arg, const struct pcap_pkthdr* pkthdr, const u_char *packet)
{
	int i = 0, *counter = (int *)arg;

	printf("Packet Count: %d\n", ++(*counter));
	printf("Received Packet Size: %d\n", pkthdr->len);
	printf("Payload:\n");
	for(i = 0; i < pkthdr->len; i++)
	{

		//printf("%d  %s\n",i, packet[i]);


		if( isprint(packet[i]) )
			printf("%c", packet[i]);
		else
			printf(". ");
		if( (i%16 == 0 && i!= 0) || i == pkthdr->len-1 )
			printf("\n");

	}
	return;
}

int main()
{
	int i = 0, count = 0;
	pcap_t *descr = NULL;
	char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);

	struct bpf_program filter;      //已经编译好的过滤器
	//char filter_app[] = "not ip[6] = 64";
    //char filter_app[] = "((ip[6:2] > 0) and (not ip[6] = 64))";  //BPF过滤规则,和tcpdump使用的是同一种过滤规则
    char filter_app[] = "host 192.168.8.182 and 192.168.8.144";  //BPF过滤规则,和tcpdump使用的是同一种过滤规则

	device = pcap_lookupdev(errbuf);

	printf("Opening device %s\n",device);

	descr = pcap_open_live(device, MAXBYTES2CAPTURE, 1, 512, errbuf);


    pcap_compile(descr, &filter, filter_app, 1, 0);
    pcap_setfilter(descr, &filter);

	pcap_loop(descr, 6, processPacket, (u_char *)&count);

	return 0;
}
