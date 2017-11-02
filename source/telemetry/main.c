#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <ipc/csp.h>
#include <ipc/socket.h>
#include <telemetry-linux/server.h>
#include <telemetry/telemetry.h>

#include <telemetry/type.h>

CSP_DEFINE_TASK(server_task)
{

    printf("Starting Telemetry Server Task\n");
    socket_conn server_conn;
    socket_conn conn;

    kprv_socket_server_setup(&server_conn, TELEMETRY_SOCKET_PORT, TELEMETRY_SUBSCRIBERS_MAX_NUM);

    while (server_conn.is_active)
    {
        while (!kprv_socket_server_accept(&server_conn, &conn))
        {
            continue;
        }

        conn.socket_handle > 0;
        conn.is_active;

        subscriber_list_item * sub = kprv_subscriber_init(conn);
        if (sub != NULL)
        {
            csp_thread_create(client_handler, NULL, 1000, sub, 0, &(sub->rx_thread));
            kprv_subscriber_add(sub);
        }
    }

    csp_thread_exit();
}

CSP_DEFINE_TASK(logging_task) {

    printf("Starting Logging Task\n");
    socket_conn conn;
    telemetry_packet in_packet;

    csp_sleep_ms(50);

    telemetry_connect(&conn);
    telemetry_subscribe(&conn, HEARTBEAT_TOPIC);

    csp_sleep_ms(10);

    while (1)
    {
        telemetry_read(&conn, &in_packet);
        printf("Received Heatbeat.\n");
        // csp_sleep_ms(100);
    }

    return CSP_TASK_RETURN;
}

int telemetry_bootstrap() {

    printf("Bootstrapping telemetry\n");
    csp_thread_handle_t server_task_handle;
    csp_thread_handle_t logging_task_handle;

    csp_thread_create(server_task, "SERVER", 1024, NULL, 0, &server_task_handle);
    csp_thread_create(logging_task, "LOGGING", 1024, NULL, 0, &logging_task_handle);

    return 1;
}
