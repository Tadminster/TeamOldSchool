#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//�̱���ȭ�� ���� ���, ��ũ��
#include "GameManager.h"
#include "Prototype.h"
#include "Player.h"

#include "ObjectManager.h"

#define GM			GameManager::GetInstance()
#define OBJ			GM->objectManager
#define DEBUGMODE	GM->debugMode
#define MAP			GM->map
#define SEA			GM->sea
#define PLAYER		GM->player