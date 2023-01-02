#ifndef TILEMAP
#define TILEMAP
#include <vector>
#include "TileSet.h"

class TileMap : public Component {
	private:
		std::vector<int> mTileMatrix;
		TileSet* mTileSet;
		int mapWidth;
		int mapHeight;
		int mapDepth;

		void _readMapInfo(std::string line, std::string delimiter);
	public:
		TileMap(GameObject& associated, std::string file, TileSet* tileSet);
		void Load(std::string file);
		int& At(int x, int y, int z = 0);
		virtual void Render();
		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
		virtual void Update(float dt);
		virtual bool Is(std::string type);
		virtual void NotifyCollision(GameObject& other) {};
		int GetWidth() { return mapWidth; };
		int GetHeight() { return mapHeight; };
		int GetDepth() { return mapDepth; };
		void SetTileSet(TileSet* tileSet) { mTileSet = tileSet; };
};

#endif // TILEMAP