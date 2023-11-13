#include "Player.h"

Player::Player(Map* map)
{
//�����ݒ�
	
		playerX = 300.0f;
		playerY = 818;
		playerRadius = 46;
		playerAliveFlag = 1;
		playerSpeed = 15;
		PlayerSizeFlag = 1;
		playerTimer = 0;
		playerMoveFlag = 0;
		playerNumber = 0;
		jumpFlag = 0;
		jumpPower = 0;
		count = 0;
		jumpNot = 0;
		jumpCount = 0;

		portionX = 1000;
		portionY = 600;
	
	// �ŐV�̃L�[�{�[�h���p
	keys[255] = { 0 };
	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	oldkeys[255] = { 0 };

	this->map = map;
}

void Player::Move()
{
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	GetHitKeyStateAll(keys);

	if (keys[KEY_INPUT_RIGHT] == 0 && oldkeys[KEY_INPUT_RIGHT] == 1)
	{
		playerMoveFlag = 0;
	}
	else if (keys[KEY_INPUT_RIGHT] == 1 && map->RightHit((int)playerX, playerY, playerRadius))
	{
		playerX += playerSpeed;
		if (playerMoveFlag == 1 || playerMoveFlag == 5)
		{
			playerMoveFlag = 2;
		}
	}

	if (keys[KEY_INPUT_LEFT] == 0 && oldkeys[KEY_INPUT_LEFT] == 1)
	{
		playerMoveFlag = 4;
	}
	else if (keys[KEY_INPUT_LEFT] == 1 && map->LeftHit((int)playerX, playerY, playerRadius))
	{
		playerX -= playerSpeed;
		if (playerMoveFlag == 1 || playerMoveFlag == 5)
		{
			playerMoveFlag = 6;
		}
	}

	if (!map->RightHit((int)playerX, playerY, playerRadius))
	{
		playerX = map->GetRight((int)playerX, playerRadius) - playerRadius;
	}
	else if (!map->LeftHit((int)playerX, playerY, playerRadius))
	{
		playerX = map->GetLeft((int)playerX, playerRadius) + map->Getblocksize() + playerRadius;
	}


	if (PlayerSizeFlag == 1 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 &&
		jumpFlag == 0 && map->DownHit((int)playerX, playerY, playerRadius) && jumpNot == 0 || PlayerSizeFlag == 1 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 &&jumpFlag == 0 && jumpNot == 1 && zCount == 0)
	{
		jumpFlag = 1;
		jumpPower = -30;

		jumpNot = 1;
	}



	if (PlayerSizeFlag == 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 &&
		jumpFlag == 0 && map->DownHit((int)playerX, playerY, playerRadius) && jumpNot == 0||
		PlayerSizeFlag == 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && jumpFlag == 0 && jumpNot == 1 && zCount == 0)
	{
		jumpFlag = 1;
		jumpPower = -40;
		jumpNot = 1;
	}

	if (PlayerSizeFlag == 0&& keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0)
	{
		PlayerSizeFlag = 1;//�ʏ�
	}
	if (map->Portion((int)playerX, playerY, playerRadius))
	{
		if (PlayerSizeFlag == 1 && keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0)
		{
			PlayerSizeFlag = 0;//�~�j
		}
	}
	Jump();
}

void Player::Jump()
{

	if (jumpFlag == 1 && map->UpHit((int)playerX, playerY, playerRadius))
	{
		playerY += jumpPower;
		jumpPower += 2;
	}

	if (jumpFlag == 0 && !map->DownHit((int)playerX, playerY, playerRadius))
	{
		playerY += jumpPower;
		jumpPower += 2;
		jumpNot = 1;
	}
	if (!map->UpHit((int)playerX, playerY, playerRadius))
	{
		playerY = map->GetUp(playerY, playerRadius) + map->Getblocksize() + playerRadius;
		jumpFlag = 0;
	}

	if (jumpFlag == 0 && map->DownHit((int)playerX, playerY, playerRadius))
	{
		playerY = map->GetDown(playerY, playerRadius) - playerRadius;
		jumpFlag = 0;
		jumpPower = 0;
	}
	/*
	if (jumpNot == 1)
	{
		jumpCount = 1;
		if(jumpCount ==1)
		{
			jumpNot = 0;
			jumpCount = 0;
		}
	}
	*/
	if (playerY - playerRadius < 0)
	{
		playerY = 0 + playerRadius;
	}

	if (jumpFlag == 1 && map->DownHit((int)playerX, playerY, playerRadius))
	{
		playerY = map->GetDown(playerY, playerRadius) - playerRadius - 4;
		jumpFlag = 0;
		jumpPower = 0;
	}
}

void Player::GraphicMove()
{
	playerTimer++;

	if (playerMoveFlag == 0 || playerMoveFlag == 2 || playerMoveFlag == 4 || playerMoveFlag == 6)
	{
		playerMoveFlag++;
		playerNumber = 0;
	}
	else if (playerMoveFlag == 1 && playerTimer >= 10)
	{
		playerNumber++;
		if (playerNumber > 7)
		{
			playerNumber = 0;
		}
		playerTimer = 0;
	}
	else if (playerMoveFlag == 3 && playerTimer >= 5)
	{
		playerNumber++;
		if (playerNumber > 3)
		{
			playerNumber = 0;
		}
		playerTimer = 0;
	}
	else if (playerMoveFlag == 5 && playerTimer >= 10)
	{
		playerNumber++;
		if (playerNumber > 7)
		{
			
			playerNumber = 0;
		}
		playerTimer = 0;
	}
	else if (playerMoveFlag == 7 && playerTimer >= 5)
	{
		playerNumber++;
		if (playerNumber > 3)
		{
			playerNumber = 0;
		}
		playerTimer = 0;
	}
}

void Player::Update()
{
	Move();
	GraphicMove();
	if (map->Hit((int)playerX, playerY, playerRadius) || playerY - playerRadius >= 960)
	{
		playerAliveFlag = 0;
		count = 1;
	}
	if (map->Clear((int)playerX, playerY, playerRadius))
	{
		count = 2;
	}

	map->Scroll(playerX);
}

void Player::Initialization()
{

		playerX = 300.0f;
		playerY = 818;
		playerRadius = 46;
		playerAliveFlag = 1;
		playerSpeed = 15;
		playerTimer = 0;
		playerMoveFlag = 0;
		playerNumber = 0;
		PlayerSizeFlag = 1;
		jumpFlag = 0;
		jumpPower = 0;
		count = 0;
		jumpNot = 0;
		jumpCount = 0;

		portionX = 1000;
		portionY = 600;
	
	}

void Player::Draw()
{
	//�`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);



	if (PlayerSizeFlag == 1)
	{
		LoadDivGraph
		(
			"Resource/chraMove.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			4,             //�O���t�B�b�N�̑���������
			4,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle2    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
		LoadDivGraph
		(
			"Resource/chraWaitMove2.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			8,             //�O���t�B�b�N�̑���������
			8,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle3    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
		LoadDivGraph
		(
			"Resource/chraWaitMove.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			8,             //�O���t�B�b�N�̑���������
			8,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
		LoadDivGraph
		(
			"Resource/chraMove2.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			4,             //�O���t�B�b�N�̑���������
			4,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle4    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);

		for (int i = 0; i < 1; i++)
		{
			DrawGraph((portionX * i) + map->GetScroll(), portionY , graphHandleP[i], TRUE);
		}
		for (int i = 0; i < 1; i++)
		{
	//		graphHandleP[i] = LoadGraph("portion.png");
		}
	}
	
	if (playerAliveFlag == 1 && playerMoveFlag == 1 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 3 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle2[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 5 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle3[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 7 && PlayerSizeFlag == 1)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle4[playerNumber], TRUE);
	}
	if (PlayerSizeFlag == 0)
	{
		LoadDivGraph
		(
			"Resource/chraMoveS.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			4,             //�O���t�B�b�N�̑���������
			4,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle2S    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
		LoadDivGraph
		(
			"Resource/chraWaitMove2S.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			8,             //�O���t�B�b�N�̑���������
			8,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle3S   //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
		LoadDivGraph
		(
			"Resource/chraWaitMoveS.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			8,             //�O���t�B�b�N�̑���������
			8,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandleS    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
		LoadDivGraph
		(
			"Resource/chraMove2S.png",  //�ǂݍ��݂����摜�t�@�C���̖��O
			4,             //�O���t�B�b�N�̑���������
			4,             //�O���t�B�b�N�̉������ɑ΂��镪����
			1,             //�O���t�B�b�N�̏c�����ɑ΂��镪����
			93,           //�O���t�B�b�N�T�C�Y
			100,            //�O���t�B�b�N�T�C�Y
			graphHandle4S    //�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�z��
		);
	}


	if (playerAliveFlag == 1 && playerMoveFlag == 1&& PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandleS[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 3 && PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle2S[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 5 && PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle3S[playerNumber], TRUE);
	}
	if (playerAliveFlag == 1 && playerMoveFlag == 7 && PlayerSizeFlag == 0)
	{
		DrawExtendGraph((playerX - playerRadius) - map->GetScroll(), playerY - playerRadius, (playerX + playerRadius) - map->GetScroll(), playerY + playerRadius, graphHandle4S[playerNumber], TRUE);
	}


}

void Player::SetPosX(double playerX)
{
	this->playerX = playerX;
}

void Player::SetPosY(int playerY)
{
	this->playerY = playerY;
}

double Player::GetPosX()
{
	return playerX;
}

int Player::GetPosY()
{
	return playerY;
}

int Player::GetRadius()
{
	return playerRadius;
}

int Player::GetCount()
{
	return count;
}