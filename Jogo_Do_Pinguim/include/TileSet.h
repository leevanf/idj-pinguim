#ifndef TILESET
#define TILESET
#include "Sprite.h"
#include <string>
#include <cstdlib>
class TileSet{
	private:
		Sprite mTileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
	public:
		TileSet(int tileWidth, int tileHeight, std::string file);
		void RenderTile(unsigned index, float x, float y);
		int GetTileHeight() { return tileHeight; };
		int GetTileWidth() { return tileWidth; };
};

#endif // TILESET