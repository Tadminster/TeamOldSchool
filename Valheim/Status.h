#pragma once
class Status
{
	friend class PlayerStatus;
private:
	UI* bgIMG = nullptr;

public:
	bool isOpen = false;
	Status();
	~Status();

	void Init();
	void Release();
	void Update();
	void Render();
};

