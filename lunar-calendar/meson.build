gnome = import('gnome')
pkg = import('pkgconfig')

version_h = configure_file(
  input: 'lunar-calendar-version.h.in',
  output : 'lunar-calendar-version.h',
  configuration : conf
  )

source_h = [
  'lunar-calendar.h',
  version_h,
  ]

source_c = [
  'lunar-calendar.c',
  'lunar-calendar-version.c',
  ]

install_headers(source_h, subdir : join_paths('lunar-calendar-3.0', 'lunar-calendar'))

liblunar_calendar = shared_library('lunar-calendar-3.0',
  source_c,
  soversion: soversion,
  version: libversion,
  dependencies: [gtk_dep, lunar_date_dep],
  include_directories: top_srcdir,
  install : true,
  install_dir : get_option('libdir')
  )

liblunar_calendar_deps = declare_dependency(sources: source_h,
  include_directories: [top_srcdir, include_directories('.')],
  dependencies: [gtk_dep, lunar_date_dep],
  link_with: liblunar_calendar)

cc = meson.get_compiler('c')
dl_dep = cc.find_library('dl')

pkg.generate(
  name: 'lunar-calendar-3.0',
  version: meson.project_version(),
  description: 'Chinese Lunar Calendar Widget Library',
  requires: ['gtk+-3.0', 'lunar-date-3.0'],
  filebase: 'lunar-calendar-@0@'.format(api_version),
  libraries: [liblunar_calendar],
  subdirs: 'lunar-calendar-3.0',
  )

if get_option('introspection')
  liblunar_calendar_gir = gnome.generate_gir(liblunar_calendar,
    sources: [source_h, source_c],
    nsversion : api_version,
    namespace : 'LunarCalendar',
    symbol_prefix : 'lunar',
    identifier_prefix : 'Lunar',
    link_with: liblunar_calendar,
    includes : ['Gtk-3.0', 'LunarDate-3.0'],
    install : true,
    install_dir_gir: girdir,
    install_dir_typelib: typelibdir,
    extra_args: [ '--c-include=lunar-calendar/lunar-calendar.h' ],
    )
  if get_option('vapi')
    lunar_date_vapi = gnome.generate_vapi('lunar-calendar-' + api_version,
      sources: liblunar_calendar_gir[0],
      packages: ['gtk+-3.0', 'lunar-date-3.0'],
      install: true,
      install_dir: vapidir,
      )
  endif
endif
