project('lunar-calendar', 'c',
  version : '3.0.1',
  license : 'LGPLv2.1+',
  meson_version : '>=0.46.0',
  default_options : [ 'warning_level=1', 'buildtype=debugoptimized', 'c_std=gnu11'],
  )

# Versionning
version_arr = meson.project_version().split('.')
lunar_calendar_version_major = version_arr[0].to_int()
lunar_calendar_version_minor = version_arr[1].to_int()
lunar_calendar_version_micro = version_arr[2].to_int()

api_version = '3.0'
soversion = 1

if lunar_calendar_version_minor.is_odd()
  lunar_calendar_interface_age = 0
else
  lunar_calendar_interface_age = lunar_calendar_version_micro
endif

# maintaining compatibility with the previous libtool versioning
# current = minor * 100 + micro - interface
# revision = interface
current = lunar_calendar_version_minor * 100 + lunar_calendar_version_micro - lunar_calendar_interface_age
revision = lunar_calendar_interface_age
libversion = '@0@.@1@.@2@'.format(soversion, current, revision)

# Compiler & Project arguments
add_project_arguments([
  '-DHAVE_CONFIG_H',
  '-I' + meson.build_root(),
  ], language: 'c')

# get suported warning flags
test_args = [
  '-fstack-protector-strong',
  '-Waggregate-return',
  '-Warray-bounds',
  '-Wcast-align',
  '-Wclobbered',
  '-Wdeclaration-after-statement',
  '-Wempty-body',
  '-Wformat=2',
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Wformat-signedness',
  '-Wignored-qualifiers',
  '-Wimplicit-function-declaration',
  '-Winit-self',
  '-Winline',
  '-Wmissing-declarations',
  '-Wmissing-format-attribute',
  '-Wmissing-include-dirs',
  '-Wmissing-noreturn',
  '-Wmissing-parameter-type',
  '-Wmissing-prototypes',
  '-Wnested-externs',
  '-Wno-discarded-qualifiers',
  '-Wno-missing-field-initializers',
  '-Wno-strict-aliasing',
  '-Wno-suggest-attribute=format',
  '-Wno-unused-parameter',
  '-Wold-style-definition',
  '-Woverride-init',
  '-Wpacked',
  '-Wpointer-arith',
  '-Wredundant-decls',
  '-Wreturn-type',
  '-Wshadow',
  '-Wsign-compare',
  '-Wstrict-aliasing',
  '-Wstrict-prototypes',
  '-Wswitch-default',
  '-Wtype-limits',
  '-Wundef',
  '-Wuninitialized',
  '-Wunused-but-set-variable',
  '-Wwrite-strings'
  ]

cc = meson.get_compiler('c')

foreach arg: test_args
  if cc.has_argument(arg)
    add_project_arguments(arg, language : 'c')
  endif
endforeach

# enable full RELRO where possible
# FIXME: until https://github.com/mesonbuild/meson/issues/1140 is fixed
global_link_args = []
test_link_args = [
  '-Wl,-z,relro',
  '-Wl,-z,now',
  ]
foreach arg: test_link_args
  if cc.has_link_argument(arg)
    global_link_args += arg
  endif
endforeach
add_global_link_arguments(
  global_link_args,
  language: 'c'
  )

# Dependencies
gtk_req_version = '>= 3.0.0'
lunar_date_req_version = '>= 2.9.0'
gtk_dep = dependency('gtk+-3.0', version: gtk_req_version)
lunar_date_dep = dependency('lunar-date-3.0', version: lunar_date_req_version)

# Configure data
conf = configuration_data()
conf.set('LUNAR_CALENDAR_MAJOR_VERSION', lunar_calendar_version_major)
conf.set('LUNAR_CALENDAR_MINOR_VERSION', lunar_calendar_version_minor)
conf.set('LUNAR_CALENDAR_MICRO_VERSION', lunar_calendar_version_micro)
conf.set('LUNAR_CALENDAR_BINARY_AGE', lunar_calendar_interface_age)

conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('GETTEXT_PACKAGE', meson.project_name())
conf.set_quoted('LUNAR_CALENDAR_LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
conf.set_quoted('DATADIR', join_paths(get_option('prefix'), get_option('datadir')))
conf.set_quoted('LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))
conf.set_quoted('BINDIR', join_paths(get_option('prefix'), get_option('bindir')))
conf.set_quoted('SYSCONFDIR', join_paths(get_option('prefix'), get_option('sysconfdir')))
conf.set_quoted('LOCALSTATEDIR', join_paths(get_option('prefix'), get_option('localstatedir')))
conf.set_quoted('LIBEXECDIR', join_paths(get_option('prefix'), get_option('libexecdir')))

configure_file(
  output : 'config.h',
  configuration : conf
  )

# Setup various paths that subdirectory meson.build files need
package_subdir = get_option('package_subdir')
girdir = join_paths(get_option('datadir'), package_subdir, 'gir-1.0')
typelibdir = join_paths(get_option('libdir'), package_subdir, 'girepository-1.0')
libdir = join_paths(get_option('libdir'), package_subdir)
if package_subdir != ''
  vapidir = join_paths(get_option('datadir'), package_subdir, 'vapi')
else
  vapidir = join_paths(get_option('datadir'), 'vala', 'vapi')
endif

top_srcdir = include_directories('.')

subdir('po')
subdir('lunar-calendar')
subdir('modules')

if get_option('docs')
  subdir('docs')
endif

if get_option('tests')
  subdir('tests')
endif
