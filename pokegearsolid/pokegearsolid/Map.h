#pragma once

#include <fstream>
#include "Defines.h"
#include <vector>

struct grid
{
	bool ground:true;
	bool empty:true;
	int cost;
	Pos worldPos;
};

struct wall
{
	Pos Size;
	Pos loc;
};

class Map
{
private:
	grid** world;
	int XSize, YSize;
	std::vector<wall> walls;
	D3Object floor, wallbase;
public:
	Map();
	Map(int X,int Y,D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture);
	bool addWall(Pos,Pos);
	bool valid(int X,int Y);
	bool display(D3Object world[],int &objs);
	bool CreMap(int x,int y,D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture);
	bool GetWorldPos(int x,int y,Pos&);
	bool getCost(int x,int y,int& cost);
	void cleanup();
	Map& operator=(const Map& temp);
	~Map();
};