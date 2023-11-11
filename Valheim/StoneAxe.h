#pragma once
class StoneAxe : public BattleItem
{
private:
	int     woodAdditionalDamage;

protected:

public:
	explicit StoneAxe(Vector3 spwanpos = Vector3 {});
	~StoneAxe();

	// BattleItem을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;


	// BattleItem을(를) 통해 상속됨
	void RenderHierarchy() override;

};

