#pragma once
class PlayerSound
{
	float soundTime = 0;
public:
	PlayerSound();
	~PlayerSound();

	void Update();
	void Walk();
	void Run();
	void Fist();
	void Swing();
};

