#pragma once
class Elder_Stone : public Unit
{
	bool goEnding{ false };
	float endingTime{ 0 };
	UI* ment;
	UI* ment2;
public:
	Elder_Stone();
	~Elder_Stone();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
};

