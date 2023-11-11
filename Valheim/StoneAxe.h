#pragma once
class StoneAxe : public BattleItem
{
private:
	int     woodAdditionalDamage;

protected:

public:
	explicit StoneAxe(Vector3 spwanpos = Vector3 {});
	~StoneAxe();

	// BattleItem��(��) ���� ��ӵ�
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;


	// BattleItem��(��) ���� ��ӵ�
	void RenderHierarchy() override;

};

