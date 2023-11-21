#pragma once
#include "StructureProto.h"

class Workbench : public StructureProto
{
private:
	friend class StructureProto;

private:
	Workbench();
	~Workbench() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	bool ReceivedDamageEvent(int damage) override;
	bool IsDestroyed() override;
	void DestructionEvent() override;

	// StructureProto을(를) 통해 상속됨
	bool interaction() override;
};

