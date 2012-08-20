/*
 * utilities.cc
 *
 *  Created on: 28.07.2012
 *      Author: cn
 */

#include "utilities.h"

#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>

Gtk::ResponseType question_dialog(const Glib::ustring title, const Glib::ustring question) {
	Gtk::MessageDialog dialog(title, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK_CANCEL, true);
	dialog.set_secondary_text(question, true);
	dialog.set_title(title);
	return (Gtk::ResponseType) dialog.run();
}

// ******************************************************************
// Logging class

std::ostringstream& Log::print(LOG_LEVEL level) {
	m_level = level;
	return os;
}

Log::~Log() {
	time_t rawtime;
	struct tm * timeinfo;
	char t_buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(t_buffer, 80, "[%x %X] ", timeinfo);

	os << std::endl;
	if (m_level < L_NOTICE) {
		fprintf(stderr, "%s: %s", t_buffer, os.str().c_str());
		fflush(stderr);
	} else {
		fprintf(stdout, "%s: %s", t_buffer, os.str().c_str());
		fflush(stdout);
	}
}

