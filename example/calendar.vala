/*
 * compilation:
 * valac --pkg lunar-calendar-3.0 calendar.vala
 *
 * configure:
 * $ ./configure --enable-vala-bindings ...
 *
 */

using Gtk;
using Lunar;

public class MyApplication : Gtk.Application {
	protected override void activate () {
		var window = new Gtk.ApplicationWindow (this);
		window.set_title ("Lunar Calendar");
		var calendar = new Lunar.Calendar ();
		window.add (calendar);
		window.show_all ();
	}
}

public int main (string[] args) {
	return new MyApplication ().run (args);
}
