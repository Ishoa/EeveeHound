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
			world[i][f].cost = 1;
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
	D3DXMatrixScaling(&floor.matrix,XSize*gridsize,YSize*gridsize,1);
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

bool Map::empt(int X,int Y)
{
	if(X>=0&&X<XSize&&Y>=0&&Y<YSize)
	{
		return world[X][Y].empty;
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
			world[i][f].ground = true;
			world[i][f].empty = true;
			world[i][f].cost = 1;
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
	D3DXMatrixScaling(&floor.matrix,XSize*gridsize,YSize*gridsize,1);
	floor.objTex = text;
	wallbase.objTex = text;
	return true;
}

void Map::resizeMap(int x,int y)
{
	cleanup();
	world = new grid*[x];
	for(int i = 0;i<x;++i)
	{
		world[i] = new grid[y];
		for(int f = 0;f<y;++f)
		{
			world[i][f].worldPos.X = i*gridsize+gridoffset;
			world[i][f].worldPos.Y = f*gridsize+gridoffset;
			world[i][f].worldPos.Z = 0;
			world[i][f].ground = true;
			world[i][f].empty = true;
			world[i][f].cost = 1;
		}
	}
	XSize = x;
	YSize = y;
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

void Map::setEmpty(int X,int Y)
{
	if(X>=0&&X<XSize&&Y>=0&&Y<YSize)
	{
		world[X][Y].empty = true;
	}
}

void Map::setNotEmpty(int X,int Y)
{
	if(X>=0&&X<XSize&&Y>=0&&Y<YSize)
	{
		world[X][Y].empty = false;
	}
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
	walls.clear();
}

bool Map::addWall(Pos pos1,Pos pos2)
{
	int XStart, XEnd, YStart,YEnd;
	wall temp;
	temp.p1 = pos1;
	temp.p2 = pos2;
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
				world[x][y].cost = 0;
			}
		}
		//add wall to list
		temp.loc = world[XStart][YEnd].worldPos;
		temp.loc.X -= gridoffset;
		temp.loc.Y += gridoffset;
		temp.Size.X = (XEnd-XStart+1)*gridsize;
		temp.Size.Y = (YStart-YEnd-1)*gridsize;
		walls.push_back(temp);
		return true;
	}
	return false;
}

bool Map::display(D3Object world[],int &objs)
{
	int temp;
	D3DXMATRIX loc, scale;
	world[objs] = floor;
	++objs;
	temp = walls.size();
	for(int i = 0;i<temp;++i)
	{
		D3DXMatrixIdentity(&wallbase.matrix);
		D3DXMatrixTranslation(&loc,walls[i].loc.X,walls[i].loc.Y,walls[i].loc.Z);
		D3DXMatrixScaling(&scale,walls[i].Size.X,walls[i].Size.Y,-3);
		wallbase.matrix = scale*loc;
		world[objs] = wallbase;
		++objs;
	}
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
			world[i][f].worldPos.Z = 1;
		}
	}
	floor = temp.floor;
	wallbase = temp.wallbase;
	return *this;
}

void Map::saveMap(std::ostream & file)
{
	file<<XSize<<"\n";
	file<<YSize<<"\n";
	file<<walls.size()<<"\n";
	for(int i = 0;i<walls.size();++i)
	{
		file<<walls[i].p1.X<<" "<<walls[i].p1.Y<<" "<<walls[i].p2.X<<" "<<walls[i].p2.Y<<"\n";
	}
}

Map::~Map()
{
	cleanup();
}