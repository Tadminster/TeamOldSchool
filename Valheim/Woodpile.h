#pragma once
#include "ItemProto.h"
class Woodpile : public MaterialProto
{
private:
	friend class ItemProto;

private:
	Woodpile();
	~Woodpile();

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render() override;
	void RenderHierarchy() override;
	bool IsDestroyed() override;
	void DestructionEvent() override;

	void Use() override;
};

