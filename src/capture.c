#include "capture.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/udp.h>

#include "dns_handler.h"

#define DNS_PORT 53

/*
 * Walks Ethernet -> IPv4/IPv6 -> UDP and, if the datagram is addressed to
 * port 53, stores the offset of the DNS payload in *payload_off.
 * Every layer is bounds-checked against `size`.
 */
static bool locate_dns_payload(const unsigned char *buf, size_t size, size_t *payload_off) {
    if (size < sizeof(struct ethhdr)) return false;

    const struct ethhdr *eth = (const struct ethhdr *)buf;
    uint16_t ethertype = ntohs(eth->h_proto);
    size_t offset = sizeof(struct ethhdr);

    if (ethertype == ETH_P_IP) {
        if (size < offset + sizeof(struct iphdr)) return false;
        const struct iphdr *ip = (const struct iphdr *)(buf + offset);
        if (ip->protocol != IPPROTO_UDP || ip->ihl < 5) return false;
        offset += (size_t)ip->ihl * 4;
    } else if (ethertype == ETH_P_IPV6) {
        if (size < offset + sizeof(struct ip6_hdr)) return false;
        const struct ip6_hdr *ip6 = (const struct ip6_hdr *)(buf + offset);
        if (ip6->ip6_nxt != IPPROTO_UDP) return false;
        offset += sizeof(struct ip6_hdr);
    } else {
        return false;
    }

    if (size < offset + sizeof(struct udphdr)) return false;
    const struct udphdr *udp = (const struct udphdr *)(buf + offset);
    if (ntohs(udp->uh_dport) != DNS_PORT) return false;
    offset += sizeof(struct udphdr);

    *payload_off = offset;
    return true;
}

int capture_open(void) {
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0)
        perror("socket (try sudo)");
    return sock;
}

int capture_run(int sock) {
    unsigned char buffer[2048];

    for (;;) {
        struct sockaddr_ll from;
        socklen_t fromlen = sizeof(from);

        ssize_t size = recvfrom(sock, buffer, sizeof(buffer), 0,(struct sockaddr *)&from, &fromlen);
        if (size < 0) {
            perror("recvfrom");
            return 1;
        }

        /* only outgoing */
        if (from.sll_pkttype != PACKET_OUTGOING) continue;

        char ifname[IF_NAMESIZE] = "?";
        if_indextoname((unsigned)from.sll_ifindex, ifname);

        size_t off;
        if (!locate_dns_payload(buffer, (size_t)size, &off)) continue;

        handle_dns(buffer + off, (size_t)size - off, ifname);
    }
}

void capture_close(int sock) {
    close(sock);
}
