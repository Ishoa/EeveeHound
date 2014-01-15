#include <fstream>
#include "Defines.h"

struct grid
{
	bool ground:true;
	bool empty:true;
	Pos worldPos;
};

class Map
{
private:
	grid** world;
	int XSize, YSize;
	
public:
	Map();
	Map(int X,int Y);
	bool addWall(Pos,Pos);
	bool valid(int X,int Y);
	bool display(D3Object world[],int &objs);
	bool CreMap(int x,int y);
	void cleanup();
	~Map();
};