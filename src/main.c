#include <stdio.h>

#include "banner.h"
#include "capture.h"

int main(void) {
    print_banner();

    int sock = capture_open();
    if (sock < 0)
        return 1;

    printf("Watching DNS queries on all interfaces (Ctrl+C to stop)...\n\n");

    int rc = capture_run(sock);

    capture_close(sock);
    return rc;
}
