#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	// ���� �߰� ���
	// 1. Contents/Sound ������ ���� ������ ����
	// 2. SOUND->AddSound("�����̸�.Ȯ����", enum class SoundName, �ݺ��������);
	
	// ���� ��� ���
	 //3. SOUND->Play("Key", ����, ��ġ, �д�);

	// BGM
	//SOUND->AddSound("bgm_title.ogg", "bgm_title", true);

	// UI
	//SOUND->AddSound("UI_move.wav", "UI_move", false);

	// PLAYER

	// Monster

	// ETC

}

SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	//SOUND->SetVolume("bgm_hankroom", 0.5f);
}