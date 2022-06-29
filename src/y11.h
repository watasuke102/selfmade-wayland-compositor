#pragma once

#include <libinput.h>
#include <libudev.h>
#include <stdlib.h>
#include <wayland-server.h>

static inline void*
zalloc(size_t size)
{
  return calloc(1, size);
}

// compositor
struct y11_compositor {
  struct wl_display* display;
  struct wl_resource* resource;

  struct y11_output* output;
  struct y11_xdg_shell_desktop* desktop;
};
struct y11_compositor*
y11_compositor_create(void);

// surface state
struct y11_surface_state {
  struct wl_resource* buffer_resource;
  int32_t sx;
  int32_t sy;
  struct y11_callback* callback;
};

void
y11_surface_state_reset(struct y11_surface_state* surface_state);

struct y11_surface_state*
y11_surface_state_create(struct wl_client* client);

void
y11_surface_state_destroy(struct y11_surface_state* surface_state);

// surface
struct y11_surface {
  struct wl_resource* resource;
  struct y11_compositor* compositor;
  struct wl_signal commit_signal;
  struct y11_surface_state* pending;
};

struct y11_surface*
y11_surface_create(struct wl_client* client, struct y11_compositor* compositor, uint32_t version,
                   uint32_t id);

void
y11_surface_destroy(struct y11_surface* surface);

// xdg shell desktop
struct y11_xdg_shell_desktop {
  struct y11_compositor* compositor;
  struct wl_list clients;
};

// output
struct y11_output {
  struct wl_list clients;
};

// region
#pragma GCC diagnostic ignored "-Wpedantic"
struct y11_region {};

struct y11_region*
y11_region_create(struct wl_client* client, uint32_t id);
