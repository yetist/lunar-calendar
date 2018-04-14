#! /usr/bin/env python2
# -*- encoding:utf-8 -*-
# FileName: python.py

import gi

gi.require_version('Gtk', '3.0')
gi.require_version('LunarCalendar', '3.0')
from gi.repository import Gtk as gtk
from gi.repository import LunarCalendar as calendar

def main_quit(object, *args):
    gtk.main_quit()

if __name__ == '__main__':
    window = gtk.Window()
    window.connect("hide", main_quit)

    cal = calendar.Calendar()
    window.add(cal)
    window.show_all()
    gtk.main()
