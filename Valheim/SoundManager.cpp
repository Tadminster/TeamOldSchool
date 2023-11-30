#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	// 사운드 추가 방법
	// 1. Contents/Sound 폴더에 사운드 파일을 넣음
	// 2. SOUND->AddSound("파일이름.확장자", enum class SoundName, 반복재생여부);
	
	// 사운드 재생 방법
	 //3. SOUND->Play("Key", 볼륨, 피치, 패닝);

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