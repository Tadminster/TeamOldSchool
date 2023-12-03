#pragma once
class ElderTrophy : public MaterialProto
{
private:
	friend class ItemProto;

private:
	ElderTrophy();
	~ElderTrophy();

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render() override;
	void RenderHierarchy() override;

	wstring GetExplain() override;

	//bool IsDestroyed() override;
	//void DestructionEvent() override;

	void Use() override;
};

