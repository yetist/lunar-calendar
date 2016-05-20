/* vi: set sw=4 ts=4: */
/*
 * lunar-calendar.c: This file is part of lunar-calendar.
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib/gi18n-lib.h>
#include <gdk/gdk.h>
#include <lunar-date/lunar-date.h>
#include <string.h>
#include <stdlib.h>
#include "lunar-calendar.h"

/**
 * SECTION:lunar-calendar
 * @Short_description: Chinese Lunar Calendar widget for GTK+
 * @Title: LunarCalendar
 *
 * The #LunarCalendar provide Chinese lunar Calendar Wieget for GTK+ .
 */

enum {
	LAST_SIGNAL
};

enum {
	PROP_0,
};

struct _LunarCalendar
{
	GtkCalendar object;
	LunarDate   *date;
	GdkRGBA     *rgba;
};

static void lunar_calendar_set_property  (GObject          *object,
		guint             prop_id,
		const GValue     *value,
		GParamSpec       *pspec);
static void lunar_calendar_get_property  (GObject          *object,
		guint             prop_id,
		GValue           *value,
		GParamSpec       *pspec);

static void lunar_calendar_month_changed (GtkCalendar *calendar, gpointer     user_data);
static void lunar_calendar_init_i18n(void);

static gchar* calendar_detail_cb (GtkCalendar *gcalendar,
		guint        year,
		guint        month,
		guint        day,
		gpointer     data);

G_DEFINE_TYPE (LunarCalendar, lunar_calendar, GTK_TYPE_CALENDAR);

static gchar *color_to_string (const GdkColor *color)
{
	PangoColor pango_color;

	pango_color.red = color->red;
	pango_color.green = color->green;
	pango_color.blue = color->blue;

	return pango_color_to_string (&pango_color);
}

static gchar *rgba_to_string (const GdkRGBA *rgba)
{
	PangoColor pango_color;

	pango_color.red = 0xffff * rgba->red;
	pango_color.green = 0xffff * rgba->green;
	pango_color.blue = 0xffff * rgba->blue;

	return pango_color_to_string (&pango_color);
}

static void lunar_calendar_dispose (GObject *gobject)
{
	LunarCalendar *calendar;

	calendar = LUNAR_CALENDAR (gobject);

	if (calendar->date != NULL)
	{
		lunar_date_free(calendar->date);
	}

	if (calendar->rgba != NULL)
		gdk_rgba_free(calendar->rgba);
	G_OBJECT_CLASS (lunar_calendar_parent_class)->dispose(gobject);
}

void  lunar_calendar_day_selected(GtkCalendar *gcalendar)
{
	guint year, month, day;
	LunarDate *lunar;
	GError *error = NULL;
	LunarCalendar *calendar;
	gchar *holiday, *format, *strtime, *color;

	calendar = LUNAR_CALENDAR(gcalendar);

	if (getenv("LUNAR_CALENDAR_IGNORE_NON_CHINESE") != NULL)
	{
		const gchar* const * langs =  g_get_language_names();

		if (langs[0] && langs[0][0] != '\0')
			if (!g_str_has_prefix(langs[0], "zh_")) {
				g_object_set (gcalendar, "show-details", FALSE, NULL);
				return;
			}
	}

	gtk_calendar_get_date(gcalendar, &year, &month, &day);
	lunar_date_set_solar_date(calendar->date, year, month + 1, day, 3, &error);
	if (error != NULL) {
		g_clear_error (&error);
		return;
	}

	color = rgba_to_string(calendar->rgba);
	holiday = lunar_date_get_holiday(calendar->date, "\n");
	format = g_strdup_printf("%s\n%s\n%s\n%s\n<span color=\"%s\">%s</span>",
			_("%(year)-%(month)-%(day)"),
			_("%(YUE)%(RI)"),
			_("%(Y60)%(M60)%(D60)"),
			_("%(shengxiao)"),
			color,
			holiday);
	strtime = lunar_date_strftime(calendar->date, format);
	g_free(color);
	g_free(holiday);
	g_free(format);

	gtk_widget_set_tooltip_markup(GTK_WIDGET(gcalendar), strtime);
	g_free(strtime);
}

static void lunar_calendar_class_init (LunarCalendarClass *class)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (class);
	GtkCalendarClass *gcalendar_class = GTK_CALENDAR_CLASS (class);

	gobject_class->dispose = lunar_calendar_dispose;
	gcalendar_class->day_selected = lunar_calendar_day_selected;
	gtk_widget_class_set_css_name (GTK_WIDGET_CLASS(class), "calendar");
}

static void lunar_calendar_init (LunarCalendar *calendar)
{
	calendar->date = lunar_date_new();
	gdk_rgba_parse(calendar->rgba, "rgba(0,0,255,1)");

	/* FIXME: here we can setup the locale info, but it looks like not a good idea */
	lunar_calendar_init_i18n();

	if (gtk_calendar_get_display_options(GTK_CALENDAR(calendar)) & GTK_CALENDAR_SHOW_DETAILS)
		gtk_calendar_set_detail_func (GTK_CALENDAR (calendar), calendar_detail_cb, calendar, NULL);
}

/**
 * lunar_calendar_new:
 * 
 * Creates a new lunar calendar, with the current date being selected. 
 * 
 * Return value: a newly #LunarCalendar widget
 **/
GtkWidget* lunar_calendar_new (void)
{
	return g_object_new (LUNAR_TYPE_CALENDAR, NULL);
}

/**
 * lunar_calendar_set_holiday_rgba:
 * @calendar: a #LunarCalendar
 * @rgba: the holiday rgba.
 *
 * Setup the holiday color.
 *
 **/
void lunar_calendar_set_holiday_rgba (LunarCalendar *calendar, const GdkRGBA *rgba)
{
	if (calendar->rgba != NULL) {
		if (gdk_rgba_equal ((gconstpointer) calendar->rgba, (gconstpointer) rgba)) {
			return;
		}
		gdk_rgba_free(calendar->rgba);
	}
	calendar->rgba = gdk_rgba_copy (rgba);
	gtk_widget_queue_draw(GTK_WIDGET(calendar));
}

/**
 * lunar_calendar_set_jieri_color:
 * @calendar: a #LunarCalendar
 * @color: the holiday color.
 *
 * Setup the holiday(jieri) color.
 *
 **/
void lunar_calendar_set_jieri_color	(LunarCalendar *calendar, const GdkColor *color)
{
	gchar *spec;
	spec = color_to_string (color);
	GdkRGBA rgba;
	rgba.red = color->red / 65535;
	rgba.green = color->green / 65535;
	rgba.blue = color->blue / 65535;
	rgba.alpha = 1;

	lunar_calendar_set_holiday_rgba(calendar, &rgba);
	gtk_widget_queue_draw(GTK_WIDGET(calendar));

	g_free(spec);
}

static gchar* calendar_detail_cb (GtkCalendar *gcalendar, guint year, guint month, guint day, gpointer data)
{
	GError *error = NULL;
	gchar *color, *value, *holiday;
	LunarCalendar *calendar;
	gboolean show_detail;

	calendar = LUNAR_CALENDAR(data);
	g_object_get (calendar, "show-details", &show_detail, NULL);
	if (! show_detail)
		return NULL;

	lunar_date_set_solar_date(calendar->date, year, month + 1, day, 0, &error);
	if (error != NULL)
	{
		g_clear_error (&error);
		return NULL;
	}

	if (getenv("LUNAR_CALENDAR_IGNORE_NON_CHINESE") != NULL)
	{
		const gchar* const * langs =  g_get_language_names();

		if (langs[0] && langs[0][0] != '\0')
			if (!g_str_has_prefix(langs[0], "zh_"))
			{
				g_object_set (calendar, "show-details", FALSE, NULL);
				return NULL;
			}
	}

	color = rgba_to_string(calendar->rgba);
	holiday = lunar_date_get_calendar(calendar->date, 3);
	value = g_strdup_printf("<span size=\"x-small\">%s</span>", holiday);
	g_free(holiday);
	return value;
}

static void lunar_calendar_init_i18n(void)
{
	static gboolean _lunar_calendar_gettext_initialized = FALSE;

	if (!_lunar_calendar_gettext_initialized)
	{
		bindtextdomain (GETTEXT_PACKAGE, LUNAR_CALENDAR_LOCALEDIR);
#ifdef HAVE_BIND_TEXTDOMAIN_CODESET
		bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif
		_lunar_calendar_gettext_initialized = TRUE;
	}
}

/*
vi:ts=4:wrap:ai:
*/
