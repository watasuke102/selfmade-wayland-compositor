#include <wayland-server.h>

#include "xdg-shell-server-protocol.h"
#include "y11.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
static void
y11_xdg_shell_desktop_bind(struct wl_client* client, void* data, uint32_t version, uint32_t id)
{
  struct y11_xdg_shell_desktop* desktop = data;
  struct y11_xdg_shell_desktop_client* desktop_client;

  desktop_client = y11_xdg_shell_desktop_client_create(client, desktop, version, id);
  if (desktop_client == NULL) {
    // TODO
  }
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
struct y11_xdg_shell_desktop*
y11_xdg_shell_desktop_create(struct y11_compositor* compositor)
{
  struct y11_xdg_shell_desktop* desktop;
  desktop = zalloc(sizeof *desktop);
  if (desktop == NULL) goto no_mem_desktop;

  if (wl_global_create(compositor->display, &xdg_wm_base_interface, 1, desktop, y11_xdg_shell_desktop_bind) ==
      NULL) {
    goto fail_create_global;
  }

  desktop->compositor = compositor;
  wl_list_init(&desktop->clients);

  compositor->desktop = desktop;

  return desktop;

fail_create_global:
  free(desktop);
no_mem_desktop:
  return NULL;
}