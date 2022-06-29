#include <wayland-server.h>

#include "xdg-shell-server-protocol.h"
#include "y11.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
struct y11_xdg_surface*
y11_xdg_surface_create(struct wl_client* client, struct y11_surface* surface,
                       struct y11_xdg_shell_desktop_client* desktop_client, uint32_t version, uint32_t id)
{
  struct y11_xdg_surface* xdg_surface;
  xdg_surface = zalloc(sizeof *xdg_surface);
  if (xdg_surface == NULL) {
    goto no_mem_xdg_surface;
  }

  return xdg_surface;

no_mem_xdg_surface:
  wl_client_post_no_memory(client);
  return NULL;
}