#include "stdafx.h"
#include "Prototype.h"

#include "Beech.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"

#include "FeatureProto.h"

std::unique_ptr<FeatureProto> FeatureProto::Create(FeatureType type)
{
	switch (type)
	{
		case FeatureType::Beech:
			return std::make_unique<Beech>();
		case FeatureType::BeechLog:
			return std::make_unique<BeechLog>();
		case FeatureType::BeechHalfLog:
			return std::make_unique<BeechHalfLog>();
		default:
			throw std::invalid_argument("error");
	}
}

void FeatureProto::Init()
{
}

void FeatureProto::Update()
{
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
