#include <wayland-server.h>

#include "xdg-shell-server-protocol.h"
#include "y11.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
struct y11_xdg_shell_desktop_client*
y11_xdg_shell_desktop_client_create(struct wl_client* client, struct y11_xdg_shell_desktop* desktop,
                                    uint32_t version, uint32_t id)
{
  struct y11_xdg_shell_desktop_client* desktop_client;

  desktop_client = zalloc(sizeof *desktop_client);
  if (desktop_client == NULL) {
    goto no_mem_desktop_client;
  }
no_mem_desktop_client:
  wl_client_post_no_memory(client);
  return NULL;
}