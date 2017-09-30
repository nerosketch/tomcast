#include "igmp.h"
#include "libfuncs/log.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>        // macro ioctl is defined


#define PACKET_LEN			IP_MAXPACKET + IGMP_MINLEN


int connect_igmp_src(void) {

	int sendsock = socket(PF_INET, SOCK_RAW, IPPROTO_IGMP);
	if (sendsock < 0) {
		LOGf("socket(SOCK_RAW): %s\n", strerror(errno));
		return -1;
	}
	const int on = 1;
	if(setsockopt(sendsock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0){
		LOGf("Setting IP_HDRINCL error: %s\n", strerror(errno));
		close(sendsock);
		return -2;
	}

    if (setsockopt(sendsock ,SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){
		LOG("Reusing ADDR failed");
		return -6;
    }

	return sendsock;
}


int igmp_rcv(int sock, int (rec_callback_func)(struct ip *, struct igmp *)){
	struct igmp *p_igmp;
	struct ip * p_ip_hdr;
	struct sockaddr_in sock_client;
	uint slen = sizeof(sock_client);

	char buf[PACKET_LEN];
	memset(buf, 0, PACKET_LEN);

	size_t recv_len;

	while(1){
		recv_len = recvfrom(sock, buf, PACKET_LEN, 0, (struct sockaddr*) &sock_client, &slen);

		if(recv_len <= 0){
			LOG("Not received data\n");
			close(sock);
			return -1;
		}
		
		p_ip_hdr = (struct ip *)buf;
		p_igmp = (struct igmp *)(buf + p_ip_hdr->ip_hl*4);

		int r = rec_callback_func(p_ip_hdr, p_igmp);
		if(r < 0){
			close(sock);
			return r;
		}

	}
	return 0;
}
