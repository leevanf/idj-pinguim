#include "TileSet.h"
#include "GameObject.h"
#include <string>
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
	mTileSet{ *(new GameObject()) , file } {
	TileSet::tileWidth = tileWidth;
	TileSet::tileHeight = tileHeight;
	rows = mTileSet.GetHeight() / tileHeight;
	columns = mTileSet.GetWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
	if (index >= 0 && index <= (tileWidth * tileHeight) - 1) {
		std::div_t tileCoordinates = std::div(index,columns);
		int tileX = tileCoordinates.rem * tileWidth;
		int tileY = tileCoordinates.quot * tileHeight;
		mTileSet.SetClip(tileX, tileY, tileWidth, tileHeight);
		mTileSet.Render(x, y);
	}
}