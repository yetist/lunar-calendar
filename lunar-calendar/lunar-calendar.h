/* SPDX-License-Identifier: LGPL-2.1-only */
/*
 * Copyright (C) 2009-2025 yetist <yetist@gmail.com>
 */

#ifndef __LUNAR_CALENDAR_H__
#define __LUNAR_CALENDAR_H__  1

#include <gtk/gtk.h>
#include <lunar-calendar/lunar-calendar-version.h>

G_BEGIN_DECLS

#define LUNAR_TYPE_CALENDAR              (lunar_calendar_get_type ())

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DECLARE_DERIVABLE_TYPE (LunarCalendar, lunar_calendar, LUNAR, CALENDAR, GtkCalendar)
struct _LunarCalendarClass
{
       GtkCalendarClass     parent_class;
       void (*activate)     (LunarCalendar *calendar);
};
#else
#define LUNAR_CALENDAR(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), LUNAR_TYPE_CALENDAR, LunarCalendar))
#define LUNAR_CALENDAR_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), LUNAR_TYPE_CALENDAR, LunarCalendarClass))
#define LUNAR_IS_CALENDAR(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LUNAR_TYPE_CALENDAR))
#define LUNAR_IS_CALENDAR_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), LUNAR_TYPE_CALENDAR))
#define LUNAR_CALENDAR_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), LUNAR_TYPE_CALENDAR, LunarCalendarClass))

typedef struct _LunarCalendar                LunarCalendar;
typedef struct _LunarCalendarClass           LunarCalendarClass;

struct _LunarCalendarClass
{
       GtkCalendarClass     parent_class;
       void (*activate)     (LunarCalendar *calendar);
};
#endif

GtkWidget*	lunar_calendar_new					(void);
void		lunar_calendar_set_holiday_rgba		(LunarCalendar *calendar, const GdkRGBA *rgba);

GLIB_DEPRECATED_FOR(lunar_calendar_set_holiday_rgba)
void		lunar_calendar_set_jieri_color		(LunarCalendar *calendar, const GdkColor *color);

G_END_DECLS

#endif /* __LUNAR_CALENDAR_H__ */
