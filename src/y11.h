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

// callback
struct y11_callback {
  struct wl_resource* resource;
};

struct y11_callback*
y11_callback_create(struct wl_client* client, uint32_t id);

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

// xdg shell desktop client
struct y11_xdg_shell_desktop_client {
  struct wl_list link;
  struct y11_xdg_shell_desktop* desktop;
  struct wl_client* client;
  struct wl_list xdg_surfaces;
};

struct y11_xdg_shell_desktop_client*
y11_xdg_shell_desktop_client_create(struct wl_client* client, struct y11_xdg_shell_desktop* desktop,
                                    uint32_t version, uint32_t id);

// xdg shell desktop
struct y11_xdg_shell_desktop {
  struct y11_compositor* compositor;
  struct wl_list clients;
};
struct y11_xdg_shell_desktop*
y11_xdg_shell_desktop_create(struct y11_compositor* compositor);

// xdg surface
struct y11_xdg_surface {
  struct wl_list link;
  struct wl_resource* resource;
  struct y11_surface* surface;
  struct y11_xdg_shell_desktop_client* desktop_client;
  struct wl_listener surface_commit_listener;
};

struct y11_xdg_surface*
y11_xdg_surface_create(struct wl_client* client, struct y11_surface* surface,
                       struct y11_xdg_shell_desktop_client* desktop_client, uint32_t version, uint32_t id);

// xdg toplevel
struct y11_xdg_toplevel {
  struct y11_xdg_surface* surface;
};

struct y11_xdg_toplevel*
y11_xdg_toplevel_create(struct wl_client* client, struct y11_xdg_surface* xdg_surface, uint32_t version,
                        uint32_t id);

// output
struct y11_output {
  struct wl_list clients;
};

// region
#pragma GCC diagnostic ignored "-Wpedantic"
struct y11_region {};

struct y11_region*
y11_region_create(struct wl_client* client, uint32_t id);
