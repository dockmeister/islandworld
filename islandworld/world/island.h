/*
 * island.h
 *
 *  Created on: 15.08.2012
 *      Author: cn
 */

#ifndef ISLAND_H_
#define ISLAND_H_

#include "islandworld.h"

#include <OgreSceneManager.h>
#include <Terrain/OgreTerrain.h>

namespace IslandWorld {

class World;

struct ImportData {
	float *terrain_data;
	Ogre::Terrain::ImportData *importdata;
};

class Island {
public:
	Island(World *world, IslandSize size = SIZE_MEDIUM);
	virtual ~Island();

	Ogre::Terrain::ImportData& get_data();

	int get_size_value(IslandSize size);
	inline int get_size_value();
	inline IslandSize get_size_info();
private:
	World *m_world;
	IslandSize m_size;
};

} /* namespace IslandWorld */
#endif /* ISLAND_H_ */
