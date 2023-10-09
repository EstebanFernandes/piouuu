#pragma once
#include<vector>
#include "CTile.h"
class CTileMap
{
private:
	std::vector<std::vector<CTile*> > tiles;
public:
	CTileMap();
	~CTileMap();
	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);
	void update();
	void render();
};

