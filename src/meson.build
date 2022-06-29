executable (
  'compositor',
  [
    'main.c',
    'compositor.c',
    'region.c',
    'surface.c',
    'surface-state.c',
    'xdg-shell-desktop.c',
    'xdg-shell-desktop-client.c',
    xdg_shell_server_protocol_h,
    xdg_shell_protocol_c,
  ],
  dependencies: [
    wayland_server_dep,
    libinput_dep,
    libudev_dep,
  ],
  install: false,
)
