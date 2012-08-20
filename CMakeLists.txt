cmake_minimum_required (VERSION 2.8)

project (islandworld)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")

set(islandworld_NAME islandworld)
set(islandworld_VERSION_MAJOR 0)
set(islandworld_VERSION_MINOR 0)
set(islandworld_VERSION_PATCH 1+devel)

IF(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
	set(islandworld_PREFIX "")
	set(islandworld_MEDIADIR ${CMAKE_BINARY_DIR}/media)
ELSE (CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
	set(islandworld_PREFIX ${CMAKE_INSTALL_PREFIX})
	set(islandworld_MEDIADIR ${CMAKE_INSTALL_PREFIX}/share/islandworld)
ENDIF (CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")

#finding packages
SET (CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/cmake)

FIND_PACKAGE (OGRE)
IF (OGRE_Terrain_FOUND)
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES})  
ELSE (OGRE_Terrain_FOUND)
  message(SEND_ERROR "OgreTerrain Library not found.")
ENDIF (OGRE_Terrain_FOUND)

FIND_PACKAGE (PkgConfig)
PKG_CHECK_MODULES (GTKMM gtkmm-3.0>=3.0 REQUIRED)


configure_file (islandworld/islandworldconfig.h.in islandworld/islandworldconfig.h)
include_directories (${CMAKE_BINARY_DIR}/islandworld)
add_subdirectory (islandworld)
add_subdirectory (tools/islandcreator)


## doxygen support
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_BINARY_DIR}/doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doxyfile WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif(DOXYGEN_FOUND)
