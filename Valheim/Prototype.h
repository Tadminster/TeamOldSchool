#include "stdafx.h"

#pragma once
class Prototype
{
protected:
	Actor* actor;

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;

	virtual Actor* GetActor() { return actor; }
	virtual void RenderHierarchy() = 0;
};

