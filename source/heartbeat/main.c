#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <ipc/csp.h>
#include <ipc/socket.h>
#include <telemetry-linux/server.h>
#include <telemetry/telemetry.h>


#include <telemetry/type.h>


static telemetry_packet out_pkt = {
    .source.topic_id = HEARTBEAT_TOPIC,
    .source.subsystem_id = 0
};

CSP_DEFINE_TASK(heartbeat_telem) {

  socket_conn conn;
  telemetry_packet in_packet;

  csp_sleep_ms(50);

  telemetry_connect(&conn);
  telemetry_subscribe(&conn, HEARTBEAT_TOPIC);

  csp_sleep_ms(10);

  while (1) {
      printf("Publishing Heatbeat.\n");
      telemetry_publish(out_pkt);
      csp_sleep_ms(1000);
  }

  csp_sleep_ms(10);

  telemetry_disconnect(&conn);

  return CSP_TASK_RETURN;
}

int heartbeat_bootstrap() {
    printf("Bootstrapping heartbeat\n");

    csp_thread_handle_t heartbeat_telem_handle;
    csp_thread_create(heartbeat_telem, "HEARTBEAT", 1024, NULL, 0, &heartbeat_telem_handle);

}
