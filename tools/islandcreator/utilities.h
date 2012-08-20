/*
 * utilities.h
 *
 *  Created on: 28.07.2012
 *      Author: cn
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

// Log macro
#define LOG(level) Log().print(level)
#define DLOG() Log().print(L_DEBUG)

#include <boost/foreach.hpp>


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <gtkmm/dialog.h>

Gtk::ResponseType question_dialog(const Glib::ustring title, const Glib::ustring question);


//
enum LOG_LEVEL {
	L_CRITICAL = 1 << 0,
	L_ERROR = 1 << 1,
	L_WARNING = 1 << 2,
	L_NOTICE = 1 << 3,
	L_DEBUG = 1 << 4
};

/** Simple logging class
 * Use the macro LOG(LOG_LEVEL l)
 */
class Log {
public:
	Log() : m_level(L_NOTICE) {};
	virtual ~Log();

	std::ostringstream& print(LOG_LEVEL level = L_NOTICE);
private:
	Log(const Log&);
	Log& operator =(const Log&);

	LOG_LEVEL m_level;
	std::ostringstream os;
};


#endif /* UTILITIES_H_ */
