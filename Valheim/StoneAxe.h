#pragma once
#include "ItemProto.h"
class StoneAxe : public WeaponProto
{
private:
	friend class ItemProto;

private:
	StoneAxe();
	~StoneAxe();

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render() override;
	void RenderHierarchy() override;

	wstring GetExplain() override;

	bool IsDestroyed() override;
	void DestructionEvent() override;

	void Use() override;
	void Fix() override;
};

