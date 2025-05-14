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

G_DECLARE_DERIVABLE_TYPE (LunarCalendar, lunar_calendar, LUNAR, CALENDAR, GtkCalendar)
struct _LunarCalendarClass
{
    GtkCalendarClass     parent_class;
    void (*activate)     (LunarCalendar *calendar);
};

GtkWidget*      lunar_calendar_new                      (void);
void            lunar_calendar_set_holiday_rgba         (LunarCalendar *calendar, const GdkRGBA *rgba);

GLIB_DEPRECATED_FOR(lunar_calendar_set_holiday_rgba)
void            lunar_calendar_set_jieri_color          (LunarCalendar *calendar, const GdkColor *color);

G_END_DECLS

#endif /* __LUNAR_CALENDAR_H__ */
