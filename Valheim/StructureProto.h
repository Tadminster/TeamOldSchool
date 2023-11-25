#pragma once

enum class StructureName
{
	Workbench
};

class StructureProto : public Prototype
{
protected:
	string		name;

public:
	static StructureProto* Create(StructureName name);
	virtual ~StructureProto() override {};
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	bool IsDestroyed() override;
	void DestructionEvent() override;

	virtual bool interaction() = 0;
};

