//
//  IslandWorld
//  *  Copyright (C) 2012 Christoph Nikic
//  *
//  *  This program is free software: you can redistribute it and/or modify
//  *  it under the terms of the GNU General Public License as published by
//  *  the Free Software Foundation, either version 3 of the License, or
//  *  (at your option) any later version.
//  *
//  *  This program is distributed in the hope that it will be useful,
//  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  *  GNU General Public License for more details.
//  *
//  *  You should have received a copy of the GNU General Public License
//  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  */

#include "world.h"
#include "island.h"

namespace IslandWorld {

World::World(Ogre::SceneManager *sm, Ogre::Light *light, WorldSize size)
	: m_scenemgr(sm), m_size(size) {

	//[ Terrain Global Options
	m_options = new Ogre::TerrainGlobalOptions();
	m_options->setMaxPixelError(8);
	m_options->setCompositeMapDistance(3000);
	m_options->setLightMapDirection(light->getDerivedDirection());
	m_options->setCompositeMapAmbient(sm->getAmbientLight());
	m_options->setCompositeMapDiffuse(light->getDiffuseColour());
	//]

	//[ TerrainGroup
	island_group = new Ogre::TerrainGroup(m_scenemgr);
	island_group
	//]

	//[ Water & Fog

	//]
}

World::~World() {
}

Island* World::create_island(IslandSize size) {
	//island_group->getTerrain(0,0)->

	return new Island(this, size);
}

float World::get_size_value(WorldSize size) {
	switch (size) {
		case SIZE_SMALL:
			return WORLD_SIZE_SMALL;
		case SIZE_MEDIUM:
			return WORLD_SIZE_MEDIUM;
		case SIZE_LARGE:
			return WORLD_SIZE_LARGE;
		case SIZE_HUGE:
			return WORLD_SIZE_HUGE;
	}
	return WORLD_SIZE_MEDIUM; //TODO: throwing exception?
}
}
