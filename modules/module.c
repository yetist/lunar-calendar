/* SPDX-License-Identifier: LGPL-2.1-only */
/*
 * Copyright (C) 2009-2025 yetist <yetist@gmail.com>
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <libintl.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <lunar-calendar/lunar-calendar.h>

void gtk_module_init(gint *argc, gchar ***argv);
static GObject* (*pre_hijacked_calendar_constructor) (GType type,
						     guint n_construct_properties,
						     GObjectConstructParam *construct_params);

static GObject* hijacked_calendar_constructor (GType type,
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

	type = lunar_calendar_get_type ();
	object = (*pre_hijacked_calendar_constructor) (type, n_construct_properties, construct_params);

	return object;
}

G_MODULE_EXPORT
void gtk_module_init (gint *argc, gchar ***argv)
{
	GObjectClass *calendar_class;

	calendar_class = g_type_class_ref (GTK_TYPE_CALENDAR);
	pre_hijacked_calendar_constructor = calendar_class->constructor;
	calendar_class->constructor = hijacked_calendar_constructor;
}
