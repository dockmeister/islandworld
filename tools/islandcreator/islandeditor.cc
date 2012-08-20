/*
 * islandeditor.cc
 *
 *  Created on: 16.08.2012
 *      Author: cn
 */

#include "islandeditor.h"

namespace IslandCreator {

IslandEditor::IslandEditor()
		: m_dirty(true), world(0), isle(0), m_light(0) {
}

IslandEditor::~IslandEditor() {
}

bool IslandEditor::is_dirty() {
	return m_dirty;
}

void IslandEditor::create_scene() {
	//[ ogre camera
	mCamera->setPosition(Ogre::Vector3(1683, 50, 2116));
	mCamera->lookAt(Ogre::Vector3(1963, 50, 1660));
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);

	if (Ogre::Root::getSingletonPtr()->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE)) {
		mCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
	}
	//]

	//[ setting up lights
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	m_light = mSceneMgr->createLight("tstLight");
	m_light->setType(Ogre::Light::LT_DIRECTIONAL);
	m_light->setDirection(lightdir);
	m_light->setDiffuseColour(Ogre::ColourValue::White);
	m_light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
	//]

	if (world == 0) {
		world = new IslandWorld::World(mSceneMgr, m_light, IslandWorld::SIZE_SMALL);
	}
}

void IslandEditor::new_island() {
	isle = world->create_island(IslandWorld::SIZE_MEDIUM);
}

} /* namespace IslandCreator */
