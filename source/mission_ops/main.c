#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <ipc/csp.h>
#include <ipc/socket.h>

int reboot() {
    printf("Rebooting\n");
//TODO
	return 0;
}


CSP_DEFINE_TASK(timeout_task) {

    printf("Starting Timeout Task\n");
    csp_sleep_ms(500);

    reboot();
    return CSP_TASK_RETURN;
}

int missionops_bootstrap() {

    printf("Bootstrapping mission ops\n");
    csp_thread_handle_t timeout_task_handle;

    csp_thread_create(timeout_task, "TIMEOUT", 1024, NULL, 0, &timeout_task_handle);

    return 1;
}
