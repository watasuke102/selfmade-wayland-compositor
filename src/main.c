#include <wayland-server.h>

#include "y11.h"

int
main(void)
{
  struct y11_compositor* compositor;
  struct y11_xdg_shell_desktop* desktop;
  const char* socket;

  compositor = y11_compositor_create();
  if (compositor == NULL) {
    return 1;
  }

  desktop = y11_xdg_shell_desktop_create(compositor);
  if (desktop == NULL) {
    return 1;
  }

  wl_display_init_shm(compositor->display);

  socket = wl_display_add_socket_auto(compositor->display);
  if (socket == NULL) {
    return 1;
  }

  wl_display_run(compositor->display);
}
