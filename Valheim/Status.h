#pragma once
class Status
{
public:
	bool isOpen = false;
private:
	UI* bgIMG = nullptr;
public:
	Status();
	~Status();

	void Init();
	void Release();
	void Update();
	void Render();
};

