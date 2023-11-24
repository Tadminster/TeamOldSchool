#pragma once

enum class LodLevel
{
    LOD0,
    LOD1,
    LOD3
};

enum class FeatureType
{
    Birch, Beech, BeechStump, BeechLog, BeechHalfLog,
    Rock
};

class FeatureProto : public Prototype
{
protected:
    
    float   gravity         { 15 };

    Vector3 rayCollisionPoint;

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
    bool ReceivedDamageEvent(int damage) override;
    bool IsDestroyed() override { return hitPoint <= 0; }
    virtual void DestructionEvent() override;
};