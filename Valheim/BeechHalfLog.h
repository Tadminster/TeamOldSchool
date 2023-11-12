#pragma once
class BeechHalfLog : public FeatureProto
{

public:
	BeechHalfLog();
	~BeechHalfLog();

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

