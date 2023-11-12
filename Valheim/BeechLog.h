#pragma once
class BeechLog : public FeatureProto
{

public:
	BeechLog();
	~BeechLog();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy() override;

	// FeatureProto��(��) ���� ��ӵ�
	void DestructionEvent() override;

	// FeatureProto��(��) ���� ��ӵ�
	void ReceivedDamageEvent(int damage) override;
};

