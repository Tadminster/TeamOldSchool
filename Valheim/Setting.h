#pragma once

class Setting
{
private:
	UI* settingPanel;


public:
	Setting();
	~Setting();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	
};

