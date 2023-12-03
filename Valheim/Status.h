#pragma once
class Status
{
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

