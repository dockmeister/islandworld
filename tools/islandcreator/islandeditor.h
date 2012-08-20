/*
 * islandeditor.h
 *
 *  Created on: 16.08.2012
 *      Author: cn
 */

#ifndef ISLANDEDITOR_H_
#define ISLANDEDITOR_H_

#include "ogrewidget.h"

#include <world/world.h>
#include <world/island.h>



namespace IslandCreator {

class IslandEditor : public OgreWidget {
public:
	IslandEditor();
	virtual ~IslandEditor();

	virtual void create_scene();
	virtual bool is_dirty();
	void new_island();

	void show_wireframe();
	void show_solid();
	void show_textured();

	void toggle_water();
	void show_water();
	void hide_water();

	void toogle_skydome();
	void show_skydome();
	void hide_skydome();
protected:
	bool m_dirty;

	IslandWorld::World *world;
	IslandWorld::Island *isle;

	Ogre::Light *m_light;
};

} /* namespace IslandCreator */
#endif /* ISLANDEDITOR_H_ */
