#include <wayland-server.h>

#include "xdg-shell-server-protocol.h"
#include "y11.h"

static void
y11_xdg_toplevel_destroy(struct y11_xdg_toplevel* xdg_toplevel);

static void
y11_xdg_toplevel_handle_destroy(struct wl_resource* resource)
{
  struct y11_xdg_toplevel* xdg_toplevel;
  xdg_toplevel = wl_resource_get_user_data(resource);
  y11_xdg_toplevel_destroy(xdg_toplevel);
}

void
dummy(void)
{
}

static const struct xdg_toplevel_interface y11_xdg_toplevel_interface = {
    .destroy = (void*)dummy,
    .set_app_id = (void*)dummy,
    .set_title = (void*)dummy,
    .set_parent = (void*)dummy,
    .show_window_menu = (void*)dummy,
    .move = (void*)dummy,
    .resize = (void*)dummy,
    .set_max_size = (void*)dummy,
    .set_min_size = (void*)dummy,
    .set_maximized = (void*)dummy,
    .unset_maximized = (void*)dummy,
    .set_fullscreen = (void*)dummy,
    .set_minimized = (void*)dummy,
};

struct y11_xdg_toplevel*
y11_xdg_toplevel_create(struct wl_client* client, struct y11_xdg_surface* xdg_surface, uint32_t version,
                        uint32_t id)
{
  struct y11_xdg_toplevel* xdg_toplevel;
  struct wl_resource* resource;

  xdg_toplevel = zalloc(sizeof *xdg_toplevel);
  if (xdg_toplevel == NULL) {
    goto no_mem_xdg_toplevel;
  }
  xdg_toplevel->surface = xdg_surface;

  resource = wl_resource_create(client, &xdg_toplevel_interface, version, id);
  if (resource == NULL) {
    goto no_mem_resource;
  }
  wl_resource_set_implementation(resource, &y11_xdg_toplevel_interface, xdg_toplevel,
                                 y11_xdg_toplevel_handle_destroy);

  return xdg_toplevel;

no_mem_resource:
  free(xdg_toplevel);

no_mem_xdg_toplevel:
  wl_client_post_no_memory(client);
  return NULL;
}

static void
y11_xdg_toplevel_destroy(struct y11_xdg_toplevel* xdg_toplevel)
{
  free(xdg_toplevel);
}
