PROJECT (islandcreator)

SET (islandcreator_SOURCES
  application.cc
  utilities.cc
  ogrewidget.cc
  islandeditor.cc
)

SET (islandworld_HEADERS
  application.h
  utilities.h
  ogrewidget.h
  islandeditor.h
)

LINK_DIRECTORIES (
  ${GTKMM_LIBRARY_DIRS}
  ${OGRE_LIBRARY_DIRS}
)

INCLUDE_DIRECTORIES (
  ${islandworld_INCLUDE_DIRS}
  ${GTKMM_INCLUDE_DIRS}
  ${OGRE_INCLUDE_DIRS}
)

ADD_EXECUTABLE ( islandcreator
  ${islandcreator_SOURCES}
) 

TARGET_LINK_LIBRARIES ( islandcreator
  world
  ${GTKMM_LIBRARIES} ${OGRE_LIBRARIES} OgreTerrain
)

