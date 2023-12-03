#pragma once
class Status
{
	UI* bgIMG = nullptr;
	bool isOpen = false;
public:
	Status();
	~Status();

	void Init();
	void Release();
	void Update();
	void Render();
};

