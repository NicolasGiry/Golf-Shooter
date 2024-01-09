#include "Map.hpp"
#include "TextureManager.hpp"





Map::Map() {
	floor = TextureManager::LoadTexture("assets/golf_floor.png");
	border = TextureManager::LoadTexture("assets/golfborder.png");

	LoadMap(lvl1);

	src.x = 0;
	src.y = 0;
	src.w = src.h = tileSize;
	dest.w = dest.h = tileSize;
	dest.x = 0;
	dest.y = 0;
}

Map::~Map() {

}

void Map::LoadMap(int array[nbRow][nbCol]) {
	for (int i = 0; i < nbRow; i++) {
		for (int j = 0; j < nbCol; j++) {
			map[i][j] = array[i][j];
		}
	}
}

void Map::DrawMap() {
	int type = 0;

	for (int i = 0; i < nbRow; i++) {
		for (int j = 0; j < nbCol; j++) {
			type = map[i][j];

			dest.x = j * tileSize;
			dest.y = i * tileSize;

			switch (type)
			{
			case 0:
				TextureManager::Draw(floor, src, dest);
				break;
			case 1:
				TextureManager::Draw(border, src, dest);
				break;
			default:
				break;
			}

		}
	}
}