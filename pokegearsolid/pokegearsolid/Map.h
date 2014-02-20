#pragma once

#include "Defines.h"
#include <vector>
#include "EntBase.h"
#include <fstream>

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
	Pos p1;
	Pos p2;
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
	bool empt(int X,int Y);
	bool display(D3Object world[],int &objs);
	bool CreMap(int x,int y,D3Object& floorbase,D3DMATERIAL9* floormat,D3DMATERIAL9* wallmat,Texture);
	bool GetWorldPos(int x,int y,Pos&);
	bool getCost(int x,int y,int& cost);
	void resizeMap(int x,int y);
	void setEmpty(int X,int Y);
	void setNotEmpty(int X,int Y);
	void cleanup();
	void saveMap(std::ostream & file);
	Map& operator=(const Map& temp);
	~Map();
};