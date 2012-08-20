//
//  applicaton.h
//
//  Author:
//       Christoph Nikic <c.nikic@gmx.de>
//
//  Copyright (c) 2012 Christoph Nikic
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "islandeditor.h"

#include <gdkmm/event.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>

namespace IslandCreator {
class Application: public Gtk::Window {
public:
	Application(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);
	virtual ~Application();
	virtual bool on_delete_event(GdkEventAny* event);
	bool hasExited() {
		return mExited;
	}

	void on_file_new();
	virtual bool on_key_press_event(GdkEventKey *event);
	virtual bool on_key_release_event(GdkEventKey *event);

protected:
	Glib::RefPtr<Gtk::Builder> m_refBuilder;
	IslandEditor *m_editor;
	bool mExited;
};
}

#endif
