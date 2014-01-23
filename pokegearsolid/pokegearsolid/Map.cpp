#include "Map.h"
#define gridsize 2
#define gridoffset 1

Map::Map()
{
	XSize = 0;
	YSize = 0;
}

Map::Map(int X,int Y,D3Object& base,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text)
{
	world = new grid*[X];
	for(int i = 0;i<X;++i)
	{
		world[i] = new grid[Y];
		for(int f = 0;f<Y;++f)
		{
			world[i][f].worldPos.X = i*gridsize+gridoffset;
			world[i][f].worldPos.Y = f*gridsize+gridoffset;
			world[i][f].worldPos.Z = 0;
		}
	}
	XSize = X;
	YSize = Y;

	floor = base;
	wallbase = base;
	floor.objMat = floormat;
	wallbase.objMat = wallmat;
	ZeroMemory(&floor.matrix,sizeof(floor.matrix));
	ZeroMemory(&wallbase.matrix,sizeof(wallbase.matrix));
	D3DXMatrixTranslation(&floor.matrix,0,0,0);
	D3DXMatrixScaling(&floor.matrix,XSize,1,YSize);
	floor.objTex = text;
	wallbase.objTex = text;
}

bool Map::valid(int X,int Y)
{
	if(X>=0&&X<XSize&&Y>=0&&Y<YSize)
	{
		return world[X][Y].ground;
	}
	return false;
}

bool Map::CreMap(int X,int Y,D3Object& base,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture text)
{
	world = new grid*[X];
	for(int i = 0;i<X;++i)
	{
		world[i] = new grid[Y];
		for(int f = 0;f<Y;++f)
		{
			world[i][f].worldPos.X = i*gridsize+gridoffset;
			world[i][f].worldPos.Y = f*gridsize+gridoffset;
			world[i][f].worldPos.Z = 0;
		}
	}
	XSize = X;
	YSize = Y;

	floor = base;
	wallbase = base;
	floor.objMat = floormat;
	wallbase.objMat = wallmat;
	ZeroMemory(&floor.matrix,sizeof(floor.matrix));
	ZeroMemory(&wallbase.matrix,sizeof(wallbase.matrix));
	D3DXMatrixScaling(&floor.matrix,XSize,1,YSize);
	floor.objTex = text;
	wallbase.objTex = text;
	return true;
}

bool Map::GetWorldPos(int x,int y,Pos& worldp)
{
	if(x>=0&&x<XSize&&y>=0&&y<YSize)
	{
		worldp = world[x][y].worldPos; 
		return true;
	}
	return false;
}

void Map::cleanup()
{
	if(XSize!=0&&YSize!=0)
	{
		for(int i = 0;i<XSize;++i)
		{
			delete [] world[i];
		}
		delete [] world;
		XSize = 0;
		YSize = 0;
	}
}

bool Map::addWall(Pos pos1,Pos pos2)
{
	int XStart, XEnd, YStart,YEnd;
	if(pos1.X >= 0&&pos2.X >= 0&&pos1.Y<YSize&&pos2.Y<YSize)
	{
		//set x range
		if(pos1.X>=pos2.X)
		{
			XStart = pos2.X;
			XEnd = pos1.X;
		}
		else
		{
			XStart = pos1.X;
			XEnd = pos2.X;
		}
		//set y range
		if(pos1.Y>=pos2.Y)
		{
			YStart = pos2.Y;
			YEnd = pos1.Y;
		}
		else
		{
			YStart = pos1.Y;
			YEnd = pos2.Y;
		}
		//create wall
		for(int x = XStart;x<=XEnd;++x)
		{
			for(int y = YStart;y<=YEnd;++y)
			{
				world[x][y].ground = false;
			}
		}
	}
	return false;
}

bool Map::display(D3Object world[],int &objs)
{
	world[objs] = floor;
	++objs;
	return true;
}

Map& Map::operator=(const Map& temp)
{
	cleanup();
	XSize = temp.XSize;
	YSize = temp.YSize;
	world = new grid*[XSize];
	for(int i = 0;i<XSize;++i)
	{
		world[i] = new grid[YSize];
		for(int f = 0;f<YSize;++f)
		{
			world[i][f].worldPos.X = i*gridsize+gridoffset;
			world[i][f].worldPos.Y = f*gridsize+gridoffset;
			world[i][f].worldPos.Z = 0;
		}
	}
	floor = temp.floor;
	wallbase = temp.wallbase;
	return *this;
}

Map::~Map()
{
	cleanup();
}