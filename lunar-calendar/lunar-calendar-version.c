/* vi: set sw=4 ts=4: */
/*
 * lunar-version.c: This file is part of lunar-calendar.
 *
 * Copyright (C) 2009-2022 yetist <yetist@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 * */

#if HAVE_CONFIG_H
#include <config.h>
#endif
#include <lunar-calendar/lunar-calendar-version.h>

/**
 * SECTION:lunar-calendar-version
 * @Short_description: Variables and functions to check the LunarCalendar version
 * @Title: Version Information
 * @include: lunar-calendar/lunar-calendar-version.h
 * @stability: Stable
 *
 * LunarCalendar provides version information, primarily useful in
 * configure checks for builds that have a configure script.
 * Applications will not typically use the features described here.
 */

const guint lunar_calendar_major_version = LUNAR_CALENDAR_MAJOR_VERSION;
const guint lunar_calendar_minor_version = LUNAR_CALENDAR_MINOR_VERSION;
const guint lunar_calendar_micro_version = LUNAR_CALENDAR_MICRO_VERSION;

/**
 * lunar_calendar_check_version:
 * @required_major: the required major version.
 * @required_minor: the required minor version.
 * @required_micro: the required micro version.
 *
 * Checks that the LunarCalendar library in use is compatible with the
 * given version. Generally you would pass in the constants
 * #LUNAR_CALENDAR_MAJOR_VERSION, #LUNAR_CALENDAR_MINOR_VERSION, #LUNAR_CALENDAR_MICRO_VERSION
 * as the three arguments to this function; that produces
 * a check that the library in use is compatible with
 * the version of LunarCalendar the application or module was compiled
 * against.
 *
 * Compatibility is defined by two things: first the version
 * of the running library is newer than the version
 * @required_major.required_minor.@required_micro. Second
 * the running library must be binary compatible with the
 * version @required_major.required_minor.@required_micro
 * (same major version.)
 *
 * Return value: %NULL if the LunarCalendar library is compatible with the
 *   given version, or a string describing the version mismatch.
 *   The returned string is owned by LunarCalendar and must not be modified
 *   or freed.
 *
 * Since: 2.4.0
 **/
const gchar * lunar_calendar_check_version (guint required_major,
                                            guint required_minor,
                                            guint required_micro)
{
    gint lunar_effective_micro = 100 * LUNAR_CALENDAR_MINOR_VERSION + LUNAR_CALENDAR_MICRO_VERSION;
    gint required_effective_micro = 100 * required_minor + required_micro;

    if (required_major > LUNAR_CALENDAR_MAJOR_VERSION)
        return "LunarCalendar version too old (major mismatch)";
    if (required_major < LUNAR_CALENDAR_MAJOR_VERSION)
        return "LunarCalendar version too new (major mismatch)";
    if (required_effective_micro < lunar_effective_micro - LUNAR_CALENDAR_BINARY_AGE)
        return "LunarCalendar version too new (micro mismatch)";
    if (required_effective_micro > lunar_effective_micro)
        return "LunarCalendar version too old (micro mismatch)";
    return NULL;
}
