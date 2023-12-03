#pragma once
#define MAX_INTROCOUNT 1.0f

class IntroScene : public Scene
{
private:
	Camera*		introCam;
	UI*			backgroundImg;
	thread*		thread1;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

