//
// IslandWorld
// Copyright (C) 2012 Christoph Nikic
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef WORLD_H_
#define WORLD_H_

#include "islandworld.h"

#include <map>
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <Terrain/OgreTerrainGroup.h>


namespace IslandWorld {

class Island;
typedef std::list<Island *> IslandGroup;

class World {
public:
	World(Ogre::SceneManager *sm, Ogre::Light *light, WorldSize size);
	virtual ~World();


	float get_size_value(WorldSize size);

	Island* create_island(IslandSize size);

	inline Ogre::SceneManager* get_scenemgr();
	inline IslandSize get_size_info();
	inline float get_size_value();
private:
	Ogre::SceneManager *m_scenemgr;

	Ogre::TerrainGlobalOptions *m_options;
	Ogre::TerrainGroup *island_group;
	
	WorldSize m_size;

};
}  // namespace IslandWorld

#include "world.hpp"

#endif
