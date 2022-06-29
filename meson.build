project (
  'wlcompositor', 'c',
  default_options: [
    'warning_level=3',
    'werror=true',
    'c_std=gnu11',
  ]
)

wayland_server_dep    = dependency('wayland-server')
wayland_scanner_dep   = dependency('wayland-scanner')
wayland_protocols_dep = dependency('wayland-protocols')
libinput_dep          = dependency('libinput')
libudev_dep           = dependency('libudev')

subdir('src')
