#include "TileMap.h"
#include "Camera.h"
#include <fstream>
#include <string>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
	Load(file);
	SetTileSet(tileSet);
}

void TileMap::_readMapInfo(std::string line, std::string delimiter) {
	mapWidth = std::stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());
	mapHeight = std::stoi(line.substr(0, line.find(delimiter)));
	line.erase(0, line.find(delimiter) + delimiter.length());
	mapDepth = std::stoi(line.substr(0, line.find(delimiter)));
}

void TileMap::Load(std::string file) {
	int token;
	size_t pos = 0;
	std::ifstream tileMapFile;
	std::string lineRead;
	std::string delimiter = ",";
	tileMapFile.open(file);
	if (tileMapFile.is_open()) {
		tileMapFile >> lineRead;
		TileMap::_readMapInfo(lineRead, delimiter);
		while (!tileMapFile.eof()) {
			tileMapFile >> lineRead;
			while ((pos = lineRead.find(delimiter)) != std::string::npos) {
				token = std::stoi(lineRead.substr(0, pos)) - 1;
				mTileMatrix.push_back(token);
				lineRead.erase(0, pos + delimiter.length());
			}
		}
	}
	else {
		std::cout << "Erro ao abrir arquivo\n";
	}
}

int& TileMap::At(int x, int y, int z) {
	return mTileMatrix.at(x + y * mapWidth + z * mapHeight * mapWidth);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int tileMatrixIndex;
	int xRenderPos;
	int yRenderPos;
	for (int yIndex = 0; yIndex < mapHeight; yIndex++) {
		for (int xIndex = 0; xIndex < mapWidth; xIndex++) {
			tileMatrixIndex = (xIndex + (yIndex * mapWidth) + (layer * mapHeight * mapWidth));
			xRenderPos = xIndex * mTileSet->GetTileWidth() + mAssociated.box.x + layer*cameraX*1.25;
			yRenderPos = yIndex * mTileSet->GetTileHeight() + mAssociated.box.y + layer*cameraY*1.25;
			mTileSet->RenderTile(mTileMatrix[tileMatrixIndex], xRenderPos, yRenderPos);
		}
	}
}

void TileMap::Render() {
	for (int z = 0; z < mapDepth; z++) {
		TileMap::RenderLayer(z, Camera::pos.x, Camera::pos.y);
	}
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(std::string type) {
	return (type == "TileMap");
}