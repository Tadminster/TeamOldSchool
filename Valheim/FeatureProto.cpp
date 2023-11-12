#include "stdafx.h"
#include "Prototype.h"

#include "Beech.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"

#include "FeatureProto.h"

FeatureProto* FeatureProto::Create(FeatureType type)
{
	switch (type)
	{
		case FeatureType::Beech:
			return new Beech();
		case FeatureType::BeechLog:
			return new BeechLog();
		case FeatureType::BeechHalfLog:
			return new BeechHalfLog();
		default:
			throw std::invalid_argument("error");
	}
}

void FeatureProto::Init()
{
}

void FeatureProto::Update()
{
	if (hitPoint <= 0)
	{
		DestructionEvent();
	}
}

void FeatureProto::LateUpdate()
{
}

void FeatureProto::Render()
{
}

void FeatureProto::RenderHierarchy()
{
}
