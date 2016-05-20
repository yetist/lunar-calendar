AC_PREREQ(2.62)

m4_define([lunar_calendar_major_version], [3])
m4_define([lunar_calendar_minor_version], [0])
m4_define([lunar_calendar_micro_version], [1])
m4_define([lunar_calendar_interface_age], [0])
m4_define([lunar_calendar_binary_age],    [m4_eval(100 * lunar_calendar_minor_version + lunar_calendar_micro_version)])
m4_define([lunar_calendar_version],       [lunar_calendar_major_version.lunar_calendar_minor_version.lunar_calendar_micro_version])
m4_define([lunar_calendar_lt_current],    [m4_eval(100 * lunar_calendar_minor_version + lunar_calendar_micro_version - lunar_calendar_interface_age)])
m4_define([lunar_calendar_lt_revision],   [lunar_calendar_interface_age])
m4_define([lunar_calendar_lt_age],        [m4_eval(lunar_calendar_binary_age - lunar_calendar_interface_age)])

AC_INIT(lunar-calendar, lunar_calendar_version, yetist@gmail.com)
AC_COPYRIGHT([Copyright (C) 2007-2011 yetist@gmail.com])

AM_INIT_AUTOMAKE([1.8 dist-bzip2 no-define -Wno-portability])

AC_CONFIG_SRCDIR(lunar-calendar/lunar-calendar.c)
AC_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])

LT_VERSION_INFO="lunar_calendar_lt_current:lunar_calendar_lt_revision:lunar_calendar_lt_age"
LT_CURRENT_MINUS_AGE=m4_eval(lunar_calendar_lt_current - lunar_calendar_lt_age)
AC_SUBST(LT_VERSION_INFO)
AC_SUBST(LT_CURRENT_MINUS_AGE)

LUNAR_CALENDAR_VERSION=lunar_calendar_version
LUNAR_CALENDAR_BINARY_AGE=lunar_calendar_binary_age
AC_SUBST(LUNAR_CALENDAR_VERSION)
AC_SUBST(LUNAR_CALENDAR_BINARY_AGE)

AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_ISC_POSIX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_LIBTOOL

AM_PATH_PYTHON

IT_PROG_INTLTOOL([0.35.0])

GTK_DOC_CHECK([1.0],[--flavour=no-tmpl])

dnl make sure we keep ACLOCAL_FLAGS around for maintainer builds to work
AC_SUBST(ACLOCAL_AMFLAGS, "$ACLOCAL_FLAGS -I m4")

GOBJECT_INTROSPECTION_CHECK([0.6.7])

AC_PATH_PROG(GLIB_MKENUMS, glib-mkenums)

dnl ================================================================
dnl check for win32 build
dnl ================================================================
AC_MSG_CHECKING([for some Win32 platform])
case "$host" in
  *-*-mingw*|*-*-cygwin*)
    platform_win32=yes
    os_win32=yes
    ;;
  *)
    platform_win32=no
    os_win32=no
    ;;
esac
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$platform_win32" = "yes")

AM_CONDITIONAL(OS_WIN32, test "$os_win32" = "yes")
AM_CONDITIONAL(OS_UNIX, test "$os_win32" != "yes")

#LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^lunar.*"'
if test "$os_win32" != yes; then
    # libtool option to control which symbols are exported
    # right now, symbols starting with _ are not exported
    LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'
else
    # We currently use .def files on Windows (for lunar-calendar)
    LIBTOOL_EXPORT_OPTIONS=
fi
AC_SUBST(LIBTOOL_EXPORT_OPTIONS)

if test "$os_win32" = "yes"; then
  AC_CHECK_TOOL(WINDRES, windres, no)
  if test "$WINDRES" = no; then
    AC_MSG_ERROR([*** Could not find an implementation of windres in your PATH.])
  fi
  AC_CHECK_PROG(ms_librarian, lib.exe, yes, no)
fi
AM_CONDITIONAL(MS_LIB_AVAILABLE, test x$ms_librarian = xyes)

dnl ================================================================
dnl  Language Support 
dnl ================================================================
GETTEXT_PACKAGE=lunar-calendar-3.0
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Define the gettext package to be used])
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT

AM_GLIB_DEFINE_LOCALEDIR(LUNAR_CALENDAR_LOCALEDIR)


dnl ================================================================
dnl check glib, gobject and liblunar
dnl ================================================================

LUNAR_DATE_REQUIRED=2.9.1
GTK2_REQUIRED=2.28.6
GDK2_REQUIRED=3.0.9

PKG_CHECK_MODULES(LUNAR_CALENDAR, lunar-date-3.0 >= $LUNAR_DATE_REQUIRED gtk+-3.0 >= $GTK2_REQUIRED  gdk-3.0 >= $GDK2_REQUIRED )

AC_SUBST(LUNAR_CALENDAR_CFLAGS)
AC_SUBST(LUNAR_CALENDAR_LIBS)

dnl ================================================================
dnl vala bindings support
dnl ================================================================
AC_ARG_ENABLE(vala-bindings,
  AC_HELP_STRING([--enable-vala-bindings],
                 [build the EXPERIMENTAL Vala bindings]),
                  enable_vala_bindings=$enableval,
                  enable_vala_bindings=no )

have_vala=no
if test x$enable_vala_bindings = xyes; then
  if test "x$INTROSPECTION_SCANNER" = x; then
    AC_MSG_ERROR([GObject-Introspection must be enabled for Vala bindings])
  fi

  AM_PROG_VALAC([0.10.0])
  have_vala=yes

  AC_PATH_PROG(VALAC, valac, valac)
  AC_SUBST(VALAC)
  AC_SUBST(VALAFLAGS)

  AC_PATH_PROG([VAPIGEN], [vapigen], [false])

  if test "x$VAPIGEN" = "xfalse"; then
    AC_MSG_ERROR([vapigen not found. Was vala compiled with --enable-vapigen?])
  fi

  AC_SUBST(VAPIGEN)
fi

AM_CONDITIONAL([HAVE_VALA], [test "x$have_vala" = "xyes"])
AC_SUBST(HAVE_VALA)


AC_CONFIG_FILES([
lunar-calendar-3.0.pc
lunar-calendar/lunar-calendar-win32.rc
lunar-calendar/Makefile
tests/Makefile
po/Makefile.in
docs/Makefile
docs/reference/Makefile
docs/reference/version.xml
Makefile
vapi/Makefile
])

AC_OUTPUT
AC_MSG_RESULT([
Build options:
  Version                   ${VERSION}
  Install prefix            ${prefix}
  Build shared libs         ${enable_shared}
  Build static libs         ${enable_static}
  CFLAGS                    ${CFLAGS}
  Build introspection       ${found_introspection}
  Build vala binding        ${have_vala}
  Build document            ${enable_gtk_doc}
])
