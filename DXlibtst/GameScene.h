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

	//�ǂݍ��݁E��������
	int GetCount();
	int GetEndFlag();

private:
	Player* player;
	Map* map;
	Change* change;
	int count;
	int endFlag;
};
