#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <ipc/csp.h>
#include <ipc/socket.h>
#include <telemetry-linux/server.h>
#include <telemetry/telemetry.h>

#include <telemetry/main.h>
#include <heartbeat/main.h>


int main(void)
{

    /* Initialize example threads */
    printf("Starting threads\n");

    telemetry_bootstrap();
    heartbeat_bootstrap();

    while (1)
    {
    	csp_sleep_ms(100000);
    }

    return 0;
}
