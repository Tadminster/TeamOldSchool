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

    Vector3 rayCollisionPoint;                  // ray�� �浹 ����(���̰� ����)

    float       hitAnimDuration { 0.0f };       // Ÿ�� �� ��鸲 �ִϸ��̼� ��� �ð�
    Vector3*    rotation;                       // Ÿ�ݽ� ��鸲 ������(actor->Find("RootNode")->rotation)
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