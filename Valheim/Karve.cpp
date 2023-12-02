#include "stdafx.h"
#include "FeatureProto.h"
#include "Karve.h"

Karve::Karve()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_Karve.xml");
	actor->name = "Karve";

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 100;
}

Karve::~Karve()
{
	delete this;
}

void Karve::Init()
{
}

void Karve::Update()
{
	FeatureProto::Update();
}

void Karve::LateUpdate()
{
}

void Karve::Render()
{
	actor->Render();
}

void Karve::Release()
{
	Karve::~Karve();
}

void Karve::RenderHierarchy()
{
	actor->RenderHierarchy();
}