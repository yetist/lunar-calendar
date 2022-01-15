/* vi: set sw=4 ts=4 wrap ai: */
/*
 * module.c: This file is part of lunar-calendar.
 *
 * Copyright (C) 2018-2022 yetist <yetist@gmail.com>
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <libintl.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <lunar-calendar/lunar-calendar.h>

void gtk_module_init(gint *argc, gchar ***argv);
static GObject* (*pre_hijacked_calendar_constructor)(GType type,
						     guint n_construct_properties,
						     GObjectConstructParam *construct_params);

static GObject* hijacked_calendar_constructor(GType type,
					      guint n_construct_properties,
					      GObjectConstructParam *construct_params)
{
	GObject *object;
	static gboolean _lunar_calendar_gettext_initialized = FALSE;

	if (!_lunar_calendar_gettext_initialized)
	{
		bindtextdomain (GETTEXT_PACKAGE, LUNAR_CALENDAR_LOCALEDIR);
		bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
		_lunar_calendar_gettext_initialized = TRUE;
	}

	type = lunar_calendar_get_type();
	object = (*pre_hijacked_calendar_constructor)(type, n_construct_properties, construct_params);

	return object;
}

G_MODULE_EXPORT
void gtk_module_init(gint *argc, gchar ***argv)
{
	GObjectClass *calendar_class;

	calendar_class = g_type_class_ref(GTK_TYPE_CALENDAR);
	pre_hijacked_calendar_constructor = calendar_class->constructor;
	calendar_class->constructor = hijacked_calendar_constructor;
}
