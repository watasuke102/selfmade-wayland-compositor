#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <wayland-server.h>

#include "y11.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
struct y11_surface*
y11_surface_create(struct wl_client* client, struct y11_compositor* compositor, uint32_t version, uint32_t id)
{
  struct y11_surface* surface;
  struct wl_resource* resource;
  struct y11_surface_state* surface_state;

  surface_state = y11_surface_state_create(client);
  if (surface_state == NULL) goto fail;

  surface = zalloc(sizeof *surface);
  if (surface == NULL) goto no_mem_surface;

  wl_signal_init(&surface->commit_signal);

  resource = wl_resource_create(client, &wl_surface_interface, version, id);
  if (resource == NULL) goto no_mem_resource;

  surface->compositor = compositor;
  surface->pending = surface_state;
  surface->resource = resource;

  return surface;

no_mem_resource:
  y11_surface_state_destroy(surface->pending);
  free(surface);
no_mem_surface:
  wl_client_post_no_memory(client);
fail:
  return NULL;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void
y11_surface_destroy(struct y11_surface* surface)
{
}
