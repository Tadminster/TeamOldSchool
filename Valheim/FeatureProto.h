#pragma once
#include "Prototype.h"

enum class FeatureType
{
    Beech, BeechLog, BeechHalfLog
};

class FeatureProto : public Prototype
{
private:


public:

    static std::unique_ptr<FeatureProto> Create(FeatureType type);
    virtual ~FeatureProto() {}

    virtual void Init() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void RenderHierarchy() override;
};