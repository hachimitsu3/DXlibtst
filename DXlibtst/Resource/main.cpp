#include "DxLib.h"
#include "Title.h"
#include "Description.h"
#include "GameScene.h"
#include "End.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "GOGO";

// �E�B���h�E����
const int WIN_WIDTH = 1400;

// �E�B���h�E�c�� 
const int WIN_HEIGHT = 960;	

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	int bgm[4];
	bgm[0] = LoadSoundMem("�����Ȗ���.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[0]);
	bgm[1] = LoadSoundMem("Hope_Amidst_Youthful_Poverty.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[1]);
	bgm[2] = LoadSoundMem("��������R���傤����.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[2]);
	bgm[3] = LoadSoundMem("b47a1cbcadc45b8c.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm[2]);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	Title* title = new Title;
	Description* description = new Description;
	GameScene* gameScene = new GameScene;
	End* end = new End;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		
		if (title->GetEndFlag() == 0)
		{
			title->Update();

			if (CheckSoundMem(bgm[1]) == 1)
			{
				StopSoundMem(bgm[1]);
			}
			if (CheckSoundMem(bgm[2]) == 1)
			{
				StopSoundMem(bgm[2]);
			}
			if (CheckSoundMem(bgm[3]) == 1)
			{
				StopSoundMem(bgm[3]);
			}
			if (CheckSoundMem(bgm[0]) == 0)
			{
				PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
			}
		}
		if(title->GetEndFlag() == 1 && description->GetEndFlag() == 0)
		{
			description->Update();
		}
		if (description->GetEndFlag() == 1 && gameScene->GetEndFlag() == 0)
		{
			gameScene->Update();

			if (CheckSoundMem(bgm[0]) == 1)
		
			{
				StopSoundMem(bgm[0]);
			}
			if (CheckSoundMem(bgm[2]) == 1)
			{
				StopSoundMem(bgm[2]);
			}
			if (CheckSoundMem(bgm[3]) == 1)
			{
				StopSoundMem(bgm[3]);
			}
			if (CheckSoundMem(bgm[1]) == 0)
			{
				PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);
			}
		}
		if(gameScene->GetEndFlag() == 1)
		{
			end->GameOver();
			end->SetNumber(1);

			if (CheckSoundMem(bgm[0]) == 1)
			{
				StopSoundMem(bgm[0]);
			}
			if (CheckSoundMem(bgm[1]) == 1)
			{
				StopSoundMem(bgm[1]);
			}
			if (CheckSoundMem(bgm[3]) == 1)
			{
				StopSoundMem(bgm[3]);
			}
			if (CheckSoundMem(bgm[2]) == 0)
			{
				PlaySoundMem(bgm[2], DX_PLAYTYPE_LOOP);
			}
		}
		if (gameScene->GetEndFlag() == 2)
		{
			end->Clear();
			end->SetNumber(2);

			if (CheckSoundMem(bgm[0]) == 1)
			{
				StopSoundMem(bgm[0]);
			}
			if (CheckSoundMem(bgm[1]) == 1)
			{
				StopSoundMem(bgm[1]);
			}
			if (CheckSoundMem(bgm[2]) == 1)
			{
				StopSoundMem(bgm[2]);
			}
			if (CheckSoundMem(bgm[3]) == 0)
			{
				PlaySoundMem(bgm[3], DX_PLAYTYPE_LOOP);
			}
		}
		if (end->GetCount() == 1)
		{
			title->Initialization();
			description->Initialization();
			gameScene->Initialization();
			end->Initialization();
		}

		// �`�揈��

		
		if (title->GetEndFlag() == 0)
		{
		//�^�C�g��
			title->Draw();
		}
		if(title->GetEndFlag() == 1  && description->GetEndFlag() == 0)
		{
			//���[������
			description->Draw();
		}
		if (description->GetEndFlag() == 1 && gameScene->GetEndFlag() == 0)
		{
			//�Q�[���{��
			gameScene->Draw();
		}
		if (gameScene->GetEndFlag() >= 1)
		{
			//�Q�[���I�[�o�[
			end->Draw();
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();	

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	
	;
}