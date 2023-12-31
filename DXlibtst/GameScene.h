#pragma once
#include "Player.h"
#include "Map.h"
#include "Change.h"

class GameScene
{
public:
	GameScene();

	void Update();
	void Initialization();
	void Draw();

	//読み込み・書き込み
	int GetCount();
	int GetEndFlag();

private:
	Player* player;
	Map* map;
	Change* change;
	int count;
	int endFlag;
};
