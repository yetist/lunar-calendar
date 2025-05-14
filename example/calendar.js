#!/usr/bin/env gjs-console

imports.gi.versions.Gtk = "3.0";
const { Gtk } = imports.gi;
const { LunarCalendar } = imports.gi;

class Application {

    constructor() {
        this.application = new Gtk.Application();

        this.application.connect('activate', this._onActivate.bind(this));
        this.application.connect('startup', this._onStartup.bind(this));
    }

    _buildUI() {
        this._window = new Gtk.ApplicationWindow({ application: this.application,
            title: "Lunar Calendar" });
        this.cal = new LunarCalendar.Calendar();
        this._window.add(this.cal);
    }

    _onActivate() {
        this._window.show_all();
    }

    _onStartup() {
        this._buildUI();
    }
};

let app = new Application();
app.application.run(ARGV);
