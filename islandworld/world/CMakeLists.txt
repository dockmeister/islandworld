PROJECT (world)

SET (world_SOURCES
  world.cc
  island.cc
)

SET (world_HEADERS
  world.h
  island.h
)

INCLUDE_DIRECTORIES (
  ${OGRE_INCLUDE_DIRS}
)

ADD_LIBRARY (world STATIC
  ${world_SOURCES}
)

