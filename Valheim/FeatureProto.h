#pragma once

enum class LodLevel
{
    LOD0,
    LOD1,
    LOD3
};

enum class FeatureType
{
    Birch, Beech, BeechStump, BeechLog, BeechHalfLog
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
    virtual void Release() override;
    virtual void RenderHierarchy() override;

public:
    bool IsDestroyed() override { return hitPoint <= 0; }
    virtual void DestructionEvent() override;
    virtual void ReceivedDamageEvent(int damage) = 0;
};