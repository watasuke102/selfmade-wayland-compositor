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

// xdg shell desktop
struct y11_xdg_shell_desktop {
  struct y11_compositor* compositor;
  struct wl_list clients;
};

// output
struct y11_output {
  struct wl_list clients;
};
