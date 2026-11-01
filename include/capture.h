#ifndef NETWORK_ANALYZER_CAPTURE_H
#define NETWORK_ANALYZER_CAPTURE_H

/*
 * Opens a raw AF_PACKET socket that sees traffic on all interfaces.
 * Returns the socket fd, or -1 on failure (errno is set; usually needs root).
 */
int capture_open(void);

/*
 * Receive loop: reads outgoing packets, extracts UDP/53 payloads and hands
 * them to handle_dns(). Runs until a receive error occurs.
 * Returns 0 on clean exit, non-zero on error.
 */
int capture_run(int sock);

/* Closes the socket returned by capture_open(). */
void capture_close(int sock);

#endif
