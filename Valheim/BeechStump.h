#pragma once

#pragma once
class BeechStump : public FeatureProto
{

public:
	BeechStump();
	~BeechStump();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy() override;

	// FeatureProto을(를) 통해 상속됨
	void DestructionEvent() override;

	// FeatureProto을(를) 통해 상속됨
	void ReceivedDamageEvent(int damage) override;
};

