CLEANFILES =

AM_CPPFLAGS =                                              \
	-I$(top_srcdir)					\
        -I$(srcdir) 					\
	$(LUNAR_CALENDAR_CFLAGS)				\
	$(WARN_CFLAGS)

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

if OS_WIN32
lunar_calendar_def = lunar-calendar.def
lunar_calendar_win32_symbols = -export-symbols $(srcdir)/lunar-calendar.def

lunar_calendar_win32_res = lunar-calendar-win32-res.o
lunar_calendar_win32_res_ldflag = -Wl,lunar-calendar-win32-res.o

lunar-calendar-win32-res.o : lunar-calendar-win32.rc
	$(WINDRES) lunar-calendar-win32.rc $@

install-def-file: lunar-calendar.def
	$(INSTALL) $(srcdir)/lunar-calendar.def $(DESTDIR)$(libdir)/lunar-calendar-win32-3.0.def

uninstall-def-file:
	-rm $(DESTDIR)$(libdir)/lunar-calendar-win32-3.0.def
else
install-def-file:
uninstall-def-file:
endif

if MS_LIB_AVAILABLE
noinst_DATA = lunar-calendar-3.0.lib

lunar-calendar-2.0.lib: liblunar-calendar-3.0.la lunar-calendar.def
	lib -machine:@LIB_EXE_MACHINE_FLAG@ -name:liblunar-calendar-3.0-$(LT_CURRENT_MINUS_AGE).dll -def:lunar-calendar.def -out:$@

install_ms_lib:
	$(INSTALL) lunar-calendar-3.0.lib $(DESTDIR)$(libdir)

uninstall_ms_lib:
	-rm $(DESTDIR)$(libdir)/lunar-calendar-3.0.lib
else
install-ms-lib:
uninstall-ms-lib:
endif

# This places the generated .def file in srcdir, since it is expected to be there.
# (The one from a tarball is)
lunar-calendar.def: lunar-calendar.symbols
	$(AM_V_GEN) (echo -e EXPORTS; $(CPP) -P -DINCLUDE_VARIABLES -DINCLUDE_INTERNAL_SYMBOLS -DG_OS_WIN32 -DALL_FILES - <$(srcdir)/lunar-calendar.symbols | sed -e '/^$$/d' -e 's/^/	/' -e 's/G_GNUC_[^ ]*//g') > $(srcdir)/lunar-calendar.def

deps =

libtool_opts =							\
  -version-info $(LT_VERSION_INFO)				\
  -export-dynamic $(no_undefined) $(LIBTOOL_EXPORT_OPTIONS)	\
  -rpath $(libdir) $(liblunar_calendar_target_ldflags)


source_h = lunar-calendar.h 
source_c = lunar-calendar.c

lib_LTLIBRARIES = liblunar-calendar-3.0.la liblunar-calendar-preload-3.0.la

liblunar_calendar_3_0_includedir = $(includedir)/liblunar-3.0/lunar-calendar
liblunar_calendar_3_0_include_HEADERS =	$(source_h)
liblunar_calendar_3_0_la_SOURCES = $(source_c)
liblunar_calendar_3_0_la_LIBADD = $(LUNAR_CALENDAR_LIBS)
liblunar_calendar_3_0_la_LDFLAGS = $(libtool_opts)
liblunar_calendar_3_0_la_DEPENDENCIES = $(deps)

if OS_WIN32
liblunar_calendar_target_ldflags = $(lunar_calendar_win32_res_ldflag) $(lunar_calendar_win32_symbols)
liblunar_calendar_3_0_la_DEPENDENCIES += $(lunar_calendar_def) $(lunar_calendar_win32_res)
endif

install-calendar-local: install-ms-lib install-def-file

liblunar_calendar_preload_3_0_includedir = $(includedir)/liblunar-3.0/lunar-calendar
liblunar_calendar_preload_3_0_include_HEADERS = $(source_h)
liblunar_calendar_preload_3_0_la_SOURCES = lunar-calendar-preload.c
liblunar_calendar_preload_3_0_la_LDFLAGS =  -version-info $(LT_VERSION_INFO)
liblunar_calendar_preload_3_0_la_LIBADD = 	\
	$(LUNAR_CALENDAR_LIBS)	\
	liblunar-calendar-3.0.la		\
	-ldl			\
	$(NULL)

if HAVE_INTROSPECTION
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS = LunarCalendar-3.0.gir
INTROSPECTION_SCANNER_ARGS = -I$(top_srcdir) -I$(srcdir) $(LUNAR_CALENDAR_CFLAGS) --warn-all --identifier-prefix=Lunar
#INTROSPECTION_COMPILER_ARGS = $(LUNAR_CALENDAR_LIBS) liblunar-calendar-3.0.la

LunarCalendar-3.0.gir: liblunar-calendar-3.0.la
LunarCalendar_3_0_gir_NAMESPACE = LunarCalendar
LunarCalendar_3_0_gir_VERSION = 3.0
LunarCalendar_3_0_gir_LIBS = $(builddir)/liblunar-calendar-3.0.la
LunarCalendar_3_0_gir_FILES = $(source_h) $(source_c)
LunarCalendar_3_0_gir_INCLUDES = Gtk-3.0 LunarDate-2.0

girdir = $(datadir)/gir-1.0
dist_gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(dist_gir_DATA) $(typelib_DATA)
endif

EXTRA_DIST =  lunar-calendar-win32.rc.in lunar-calendar.symbols

-include $(top_srcdir)/git.mk
