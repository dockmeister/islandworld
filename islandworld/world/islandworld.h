/*
 * islandworld.h
 *
 *  Created on: 19.08.2012
 *      Author: cn
 */

#ifndef ISLANDWORLD_H_
#define ISLANDWORLD_H_

namespace IslandWorld {

enum WorldSize {
	SIZE_SMALL,
	SIZE_MEDIUM,
	SIZE_LARGE,
	SIZE_HUGE
};

typedef WorldSize IslandSize;

#define WORLD_SIZE_SMALL 5000.
#define WORLD_SIZE_MEDIUM 8000.
#define WORLD_SIZE_LARGE 10000.
#define WORLD_SIZE_HUGE 120000.
#define ISLAND_SIZE_SMALL 65
#define ISLAND_SIZE_MEDIUM 129
#define ISLAND_SIZE_LARGE 257
#define ISLAND_SIZE_HUGE 513

}



#endif /* ISLANDWORLD_H_ */
