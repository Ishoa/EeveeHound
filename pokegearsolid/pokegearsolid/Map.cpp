#include "Map.h"

Map::Map()
{
}

Map::Map(int X,int Y)
{
	world = new grid*[X];
	for(int i = 0;i<X;++i)
	{
		world[i] = new grid[Y];
		for(int f = 0;f<Y;++f)
		{
			world[i][f].worldPos.X = i;
			world[i][f].worldPos.Y = f;
			world[i][f].worldPos.Z = 0;
		}
	}
	XSize = X;
	YSize = Y;
}

bool Map::valid(int X,int Y)
{
	if(X>=0&&X<XSize&&Y>=0&&Y<YSize)
	{
		return world[X][Y].ground;
	}
	return false;
}

bool Map::CreMap(int X,int Y)
{
	if(X>0&&Y>0)
	{
		world = new grid*[X];
		for(int i = 0;i<X;++i)
		{
			world[i] = new grid[Y];
		}
		XSize = X;
		YSize = Y;
		return true;
	}
	return false;
}

void Map::cleanup()
{
	for(int i = 0;i<XSize;++i)
	{
		delete [] world[i];
	}
	delete [] world;
	XSize = 0;
	YSize = 0;
}

Map::~Map()
{
	cleanup();
}