#include "ogrewidget.h"

#include <iostream>

#include <gtkmm/requisition.h>
#include <glibmm/main.h>
#include <glibmm/timer.h>
#include <gdkmm/window.h>
#include <gdkmm/event.h>
#include <gdk/gdkx.h>

OgreWidget::OgreWidget()
		: Gtk::Widget(), mRenderWindow(0), mSceneMgr(0), mViewport(0), mCamera(0) {
	set_has_window(false);
	set_margin_bottom(5);
	set_margin_left(5);
	set_margin_right(5);
	set_margin_top(5);
	mWidth = mHeight = 20;
}

OgreWidget::~OgreWidget() {
	if (mRenderWindow) {
		Ogre::Root::getSingleton().detachRenderTarget(mRenderWindow);
		delete mRenderWindow;
	}
}

void OgreWidget::on_size_request(Gtk::Requisition* requisition) {
	*requisition = Gtk::Requisition();
	int w = 800;
	int h = 600;
	if (w < 2) w = 2;
	if (h < 2) h = 2;
	requisition->height = h;
	requisition->width = w;
}

void OgreWidget::on_size_allocate(Gtk::Allocation& allocation) {
	set_allocation(allocation);
	if (get_realized()) {
		if (mRefGdkWindow) {
			mRefGdkWindow->move_resize(allocation.get_x(), allocation.get_y(), allocation.get_width(), allocation.get_height());
		}

		if (mRenderWindow) {
			mRenderWindow->resize(allocation.get_width(), allocation.get_height());
			mRenderWindow->windowMovedOrResized();
			mCamera->setAspectRatio(Ogre::Real(allocation.get_width()) / Ogre::Real(allocation.get_height()));
			on_expose_event(NULL);
		}
	}
}

void OgreWidget::on_map() {
    Glib::signal_idle().connect( sigc::mem_fun(*this, &OgreWidget::on_idle) );
	//Call base class:
	Gtk::Widget::on_map();
}

void OgreWidget::on_unmap() {
	//Call base class:
	Gtk::Widget::on_unmap();
}

void OgreWidget::on_realize() {
	//Call base class:
	    Gtk::Widget::on_realize();
	    Gtk::Allocation allocation = get_allocation();
	    if(!mRefGdkWindow)
	    {
	        //Create the GdkWindow:
	        GdkWindowAttr attributes;
	        memset(&attributes, 0, sizeof(attributes));

	        //Set initial position and size of the Gdk::Window:
	        attributes.x = allocation.get_x();
	        attributes.y = allocation.get_y();
	        attributes.width = allocation.get_width();
	        attributes.height = allocation.get_height();

	        attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK | Gdk::ALL_EVENTS_MASK ;
	        attributes.window_type = GDK_WINDOW_CHILD;
	        attributes.wclass = GDK_INPUT_OUTPUT;

	        mRefGdkWindow = Gdk::Window::create(get_window(), &attributes, GDK_WA_X | GDK_WA_Y);

	        mWidth =  attributes.width;
	        mHeight = attributes.height;

	    }

	    if (!mRenderWindow)
	    {

	        Ogre::NameValuePairList params;
	    #ifdef WIN32 // who cares
	        params["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)GDK_WINDOW_HWND(mRefGdkWindow->gobj()));
	    #else
	       GdkWindow* parent = mRefGdkWindow->gobj();
	       GdkDisplay* display = gdk_window_get_display(parent);
	       GdkScreen* screen = gdk_window_get_screen(parent);

	       Display* xdisplay = GDK_DISPLAY_XDISPLAY(display);
	       Screen* xscreen = GDK_SCREEN_XSCREEN(screen);
	       int screen_number = XScreenNumberOfScreen(xscreen);
	       XSync(xdisplay, true);
	       XID xid_parent = GDK_WINDOW_XID(parent);

	       params["externalWindowHandle"] = Ogre::StringConverter::toString(static_cast<unsigned long>(xid_parent));

	    #endif

	        mRenderWindow = Ogre::Root::getSingleton().createRenderWindow("GtkOgre" + mName,
	        allocation.get_width(), allocation.get_height(), false, &params);

	        mRenderWindow->setAutoUpdated(false);
	        set_has_window(true);

	        set_window(mRefGdkWindow);

	        set_double_buffered(true);
	        //make the widget receive expose events
	        mRefGdkWindow->set_user_data(gobj());
	        //mRefGdkWindow->set_back_pixmap(Glib::RefPtr<Gdk::Pixmap>(),false);

	        init_ogre();
	    }
}

void OgreWidget::on_unrealize() {
	mRefGdkWindow.clear();
	//Call base class:
	Gtk::Widget::on_unrealize();
}

bool OgreWidget::on_expose_event(GdkEventExpose* event) {

	if (mRenderWindow) {
        Ogre::Root::getSingletonPtr()->_fireFrameStarted();
        Ogre::Root::getSingletonPtr()->_fireFrameRenderingQueued();
        mRenderWindow->update(true);
        Ogre::Root::getSingletonPtr()->_fireFrameEnded();
	}
	return true;
}

bool OgreWidget::on_idle() {
	on_expose_event(0);
	return true;
}

void OgreWidget::init_ogre() {
	// Set default mipmap level & texture filtering
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_TRILINEAR);

	// Create scene manager
	mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

	// Create the camera
	mCamera = mSceneMgr->createCamera("Camera");

	// Create one viewport, entire window
	mViewport = mRenderWindow->addViewport(mCamera);

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

	create_scene();
}

bool OgreWidget::on_motion_notify_event(GdkEventMotion *event) {
	std::cout << ".";
	return true;
}

bool OgreWidget::on_button_press_event(GdkEventButton *event) {
	std::cout << "button press\n";
	return true;
}

bool OgreWidget::on_button_release_event(GdkEventButton *event) {
	std::cout << "button release\n";
	return true;
}
