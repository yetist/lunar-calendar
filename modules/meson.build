liblunar_calendar_module = shared_library('lunar-calendar-module',
  'module.c',
  soversion: soversion,
  version: libversion,
  dependencies: [gtk_dep, liblunar_calendar_deps, dl_dep],
  include_directories: top_srcdir,
  install : true,
  install_dir : join_paths(get_option('libdir'), 'gtk-3.0', 'modules')
  )
