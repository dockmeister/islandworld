//
//  application.cc
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
#include <islandworldconfig.h>

#include "application.h"
#include "utilities.h"

#include <gtkmm.h>
#include <boost/bind.hpp>

#define GLADE_FILENAME "islandeditor.glade"

namespace IslandCreator {

Application::Application(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
		: Gtk::Window(cobject), m_refBuilder(builder), mExited(false) {

	Gtk::Paned *grid;
	m_refBuilder->get_widget("paned2", grid);

	m_editor = new IslandEditor;
	grid->add2(*m_editor);
	show_all();

	Glib::RefPtr<Gtk::Action> action = Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("file_new"));
	action->signal_activate().connect(boost::bind(&Application::on_file_new, this));
}

Application::~Application() {
}

void Application::on_file_new() {
	if(m_editor->is_dirty()) {
		if(question_dialog("Unsaved Changes", "There are unsaved changes, any data will be lost! Do you want to continue?") == Gtk::RESPONSE_CANCEL) {
			return;
		}
	}

	m_editor->new_island();
}

bool Application::on_delete_event(GdkEventAny* event) {
	mExited = true;
	return false;
}

bool Application::on_key_press_event(GdkEventKey *event) {
	std::cout << "keydown\n";
	return true;
}

bool Application::on_key_release_event(GdkEventKey *event) {
	std::cout << "keyup\n";
	return true;
}
}

int main(int argc, char *argv[]) {
	//[ Init Ogre
	Ogre::Root* root = new Ogre::Root();

	Ogre::RenderSystem* rsys = root->getRenderSystemByName("OpenGL Rendering Subsystem");
	rsys->setConfigOption("Full Screen", "No");
	rsys->setConfigOption("VSync", "No");
	rsys->setConfigOption("FSAA", "0");
	rsys->setConfigOption("sRGB Gamma Conversion", "No");

	root->setRenderSystem(rsys);
	root->initialise(false);
	//]

	//[ Init Gtk
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try {
		//TODO: setting up path search "../share/"
		refBuilder->add_from_file(Glib::ustring(ISLANDWORLD_MEDIADIR) + Glib::ustring("/") + Glib::ustring(GLADE_FILENAME));
	} catch (Glib::Exception &ex) {
		std::cerr << "Glade error: " << ex.what() << std::endl;
		return 1;
	}

	IslandCreator::Application *app;
	refBuilder->get_widget_derived("island_editor_window", app);

	//]

	app->show();

	while (!app->hasExited()) {
		kit.iteration();
		// you could also call renderOneFrame() here instead.
		root->renderOneFrame();
	}

	delete app;
	delete root;
	return 0;
}
