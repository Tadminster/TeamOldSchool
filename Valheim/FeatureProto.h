#pragma once

enum class FeatureType
{
    Beech, BeechLog, BeechHalfLog
};

class FeatureProto : public Prototype
{
protected:
    int hitPoint;

public:

    static FeatureProto* Create(FeatureType type);
    virtual ~FeatureProto() {}

    virtual void Init() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void RenderHierarchy() override;

protected:
    virtual void DestructionEvent() = 0;
    virtual void ReceivedDamageEvent(int damage) = 0;
};