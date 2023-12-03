#pragma once
#include "ItemProto.h"

class FineAxe : public WeaponProto
{
private:
	friend class ItemProto;

private:
	FineAxe();
	~FineAxe();

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

