#pragma once
#include "ItemProto.h"
class StoneAxe : public WeaponProto
{
private:

public:
	StoneAxe();
	~StoneAxe();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render() override;
	void RenderHierarchy() override;
	bool IsDestroyed() override;
	void DestructionEvent() override;

	void Use() override;
	void Fix() override;
};

