#!/usr/bin/env python
# -*- encoding:utf-8 -*-
# FileName: python.py

import gi

gi.require_version('Gtk', '3.0')
gi.require_version('LunarCalendar', '3.0')
from gi.repository import Gtk
from gi.repository import LunarCalendar
import sys

class CalWindow(Gtk.ApplicationWindow):
    def __init__(self, app):
        Gtk.Window.__init__(self, title="Lunar Calendar", application=app)
        calendar = LunarCalendar.Calendar()
        self.add(calendar)

class CalApplication(Gtk.Application):

    def __init__(self):
        Gtk.Application.__init__(self)

    def do_activate(self):
        win = CalWindow(self)
        win.show_all()

    def do_startup(self):
        Gtk.Application.do_startup(self)

if __name__ == '__main__':
    app = CalApplication()
    exit_status = app.run(sys.argv)
    sys.exit(exit_status)
