#pragma once
#include "ItemProto.h"

class WoodShield : public ShieldProto
{
private:
	friend class ItemProto;

private:
	WoodShield();
	~WoodShield();

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

