NULL=

AM_CPPFLAGS =                                              \
	-I$(top_srcdir)					\
	-I$(top_srcdir)/lunar-calendar			\
        -I$(srcdir) 					\
	$(LUNAR_CALENDAR_CFLAGS)				\
	$(NULL)

noinst_PROGRAMS = test-calendar

test_calendar_SOURCES =  test-calendar.c

LIBS =                       		\
        $(LUNAR_CALENDAR_LIBS)       		\
        $(top_builddir)/lunar-calendar/liblunar-calendar-3.0.la

-include $(top_srcdir)/git.mk
