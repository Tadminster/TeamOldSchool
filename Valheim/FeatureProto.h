#pragma once
#define MAXMUM_UPDATE_DISTANCE 3000.0f

enum class FeatureType
{
    Birch, Beech, BeechStump, BeechLog, BeechHalfLog,
    Rock
};

class FeatureProto : public Prototype
{
protected:
    
    float   gravity         { 15.0f };

    Vector3 rayCollisionPoint;                  // ray와 충돌 지점(높이값 계산용)

    float       hitAnimDuration { 0.0f };       // 타격 후 흔들림 애니메이션 재생 시간
    Vector3*    rotation;                       // 타격시 흔들림 조절용(actor->Find("RootNode")->rotation)
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
    virtual void LodUpdate(float distance) {};

    virtual bool ReceivedDamageEvent(float damage);
    virtual void ReceivedDamageAnimation();
    bool IsDestroyed() override { return hitPoint <= 0; }
    virtual void DestructionEvent() override;
};