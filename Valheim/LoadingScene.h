#pragma once
#define MAX_LOADCOUNT	7.0f
#define LOADIND_RATE	DELTA * 25.0f

class LoadingScene : public Scene
{
private:
	Camera*		loadingCam;
	UI*			backgroundImg;
	thread*		thread1;

	RECT		textPos;
	float       loadingProgress{ 0.0f };

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

