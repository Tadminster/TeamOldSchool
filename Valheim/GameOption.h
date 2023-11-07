#pragma once
class GameOption : public Actor
{
private:
	UI*             gameOption;
protected:

public:
	GameOption();
	~GameOption();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();

};

