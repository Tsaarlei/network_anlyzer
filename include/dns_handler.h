#ifndef NETWORK_ANALYZER_DNS_HANDLER_H
#define NETWORK_ANALYZER_DNS_HANDLER_H

#include <stddef.h>

/*
 * Parses a raw DNS payload (the bytes after the UDP header).
 * If it is a query with at least one question, prints one line:
 *   [ifname] TYPE   name
 * Responses and malformed packets are silently ignored.
 */
void handle_dns(const unsigned char *dns, size_t len, const char *ifname);

#endif
