#include "stdafx.h"

#pragma once
class Prototype
{
protected:
	Actor*		actor;
	Ray			groundRay;
	float		hitPoint;
public:
	virtual ~Prototype() 
	{ 
		actor->Release(); 
		actor = nullptr;
	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void RenderHierarchy() = 0;

	virtual Actor* GetActor() { return actor; }

	// @brief ������Ʈ�� �������� ����� �� ȣ���ϴ� �Լ�
	// @param damage ��������
	virtual bool ReceivedDamageEvent(float damage) = 0;

	// @brief ������Ʈ�� �ı��Ǵ� ������ �˻��ϴ� �Լ�
	// @brief ���� ���, ü���� 0 �����̰ų� �������� ���� ����ǰ� �����ð��� ������ ��
	// @return �ı��Ǿ�� �ϴ� ��� true, �ƴ� ��� false
	virtual bool IsDestroyed() = 0;

	// @brief ������Ʈ�� �ı��Ǿ��� �� ȣ��Ǵ� �Լ�
	// @brief ���� ���, ������ �ı��Ǹ� ������ �������� ��ƼŬ�� ����ϰ�, �볪�� ������Ʈ�� ����.
	// @brief ���Ͱ� �ı��Ǹ� �������� ���.
	virtual void DestructionEvent() = 0;
};

