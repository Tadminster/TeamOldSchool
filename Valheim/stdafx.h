#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//플레이어 싱글턴화를 위한 헤더, 매크로
#include "Prototype.h"
#include "Player.h"
#define player Player::GetInstance()