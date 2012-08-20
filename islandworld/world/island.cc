/*
 * island.cc
 *
 *  Created on: 15.08.2012
 *      Author: cn
 */

#include "island.h"
#include "world.h"
namespace IslandWorld {

Island::Island(World *world, IslandSize size)
	: Ogre::Terrain(world->get_scenemgr()), m_world(world) {
	Terrain::ImportData imp;
	imp.terrainSize = get_size_value(size);
	imp.worldSize = world->get_size_value();
	imp.inputScale = 1.0;
	imp.constantHeight = 1.0;
	prepare(imp);
}

Island::~Island() {
	// TODO Auto-generated destructor stub
}

int Island::get_size_value(IslandSize size) {
	switch (size) {
		case SIZE_SMALL:
			return ISLAND_SIZE_SMALL;
		case SIZE_MEDIUM:
			return ISLAND_SIZE_MEDIUM;
		case SIZE_LARGE:
			return ISLAND_SIZE_LARGE;
		case SIZE_HUGE:
			return ISLAND_SIZE_HUGE;

	}
	return ISLAND_SIZE_MEDIUM; //TODO: throwing exception?
}
} /* namespace IslandWorld */
