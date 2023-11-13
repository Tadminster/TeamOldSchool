#include "stdafx.h"

#pragma once
class Prototype
{
protected:
	Actor* actor;

public:
	virtual ~Prototype() 
	{ 
		actor->Release(); 
		actor = nullptr;
	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void RenderHierarchy() = 0;

	virtual Actor* GetActor() { return actor; }

	// @brief 오브젝트가 파괴되는 조건을 검사하는 함수
	// @brief 예를 들어, 체력이 0 이하이거나 아이템이 땅에 드랍되고 일정시간이 지났을 때
	// @return 파괴되어야 하는 경우 true, 아닌 경우 false
	virtual bool DestructionEvent() = 0;
};

