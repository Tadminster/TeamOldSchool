#pragma once
class Craft
{
	friend class Player;

private:
	UI*		craftUI;

public:
	Craft();
	~Craft();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();
};

