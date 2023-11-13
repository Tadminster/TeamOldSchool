#pragma once
//#include "Prototype.h"
//#include "FeatureProto.h"
class BeechLog : public FeatureProto
{

public:
	BeechLog();
	~BeechLog();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	// FeatureProto��(��) ���� ��ӵ�
	void DestructionEvent() override;
	void ReceivedDamageEvent(int damage) override;
};

