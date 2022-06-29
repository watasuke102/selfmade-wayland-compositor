#include <wayland-server.h>

#include "y11.h"

struct y11_compositor*
y11_compositor_create(void)
{
  struct y11_compositor* compositor;
  struct wl_display* display;

  compositor = zalloc(sizeof *compositor);
  if (compositor == NULL) goto fail;

  display = wl_display_create();

  compositor->display = display;
  compositor->output = NULL;
  compositor->desktop = NULL;

  // TODO

  return compositor;
fail:
  return NULL;
}