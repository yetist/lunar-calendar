/* vi: set sw=4 ts=4: */
/*
 * lunar-calendar.h: This file is part of lunar-calendar.
 *
 * Copyright (C) 2009 yetist <yetist@gmail.com>
 *
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

#ifndef __LUNAR_CALENDAR_H__ 
#define __LUNAR_CALENDAR_H__  1

#include <gtk/gtk.h>
#include <lunar-calendar/lunar-calendar-version.h>

G_BEGIN_DECLS

#define LUNAR_TYPE_CALENDAR              (lunar_calendar_get_type ())

G_DECLARE_FINAL_TYPE (LunarCalendar, lunar_calendar, LUNAR, CALENDAR, GtkCalendar)

GtkWidget*	lunar_calendar_new					(void);
void		lunar_calendar_set_holiday_rgba		(LunarCalendar *calendar, const GdkRGBA *rgba);

GLIB_DEPRECATED_FOR(lunar_calendar_set_holiday_rgba)
void		lunar_calendar_set_jieri_color		(LunarCalendar *calendar, const GdkColor *color);

G_END_DECLS

#endif /* __LUNAR_CALENDAR_H__ */

/*
vi:ts=4:wrap:ai:
*/
