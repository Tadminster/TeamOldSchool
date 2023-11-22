#pragma once

class UI : public Actor
{
protected:
	bool			 Press = false;
	
public:
	Vector2			 pivot;
	static UI*		Create(string name = "UI");
	bool			MouseOver(class Camera* cam = Camera::main);
	bool			MousePress(class Camera* cam = Camera::main);
	bool			MouseDown(class Camera* cam = Camera::main);
	void			RenderDetail();

	function<void()> mouseOver = nullptr;	// 마우스가 위에 존재할 때
	function<void()> mouseDown = nullptr;	// 마우스가 위에 존재하고, 클릭했을 때
	function<void()> mousePress = nullptr;	// 누르고 있을 때
	function<void()> mouseUp = nullptr;		// 누르고 떼었을 때

	virtual void	Update() override;
	void			Render(shared_ptr<Shader> pShader = nullptr);
};

