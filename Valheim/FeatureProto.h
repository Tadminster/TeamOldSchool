#pragma once
#define MAXMUM_UPDATE_DISTANCE 2000.0f

enum class FeatureType
{
    Birch, 
    Beech, //BeechInstancing, BeechStump, BeechLog, BeechHalfLog,
    Rock,
    Karve, Shipwreck
};

enum class RenderType
{
	Normal, Instancing
};

enum class FeatureArmorType
{
    Tree, Rock
};

class FeatureProto : public Prototype
{
protected:
    FeatureArmorType    type;
    float               gravity         { 15.0f };

    Vector3             rayCollisionPoint;              // ray�� �浹 ����(���̰� ����)

    float               hitAnimDuration { 0.0f };       // Ÿ�� �� ��鸲 �ִϸ��̼� ��� �ð�
    Vector3*            rotation;                       // Ÿ�ݽ� ��鸲 ������(actor->Find("RootNode")->rotation)

    float               playerDistance;                 // �÷��̾�� ������Ʈ�� �Ÿ�
public:

    static FeatureProto* Create(FeatureType featureType);
    virtual ~FeatureProto() {}

    virtual void Init() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void RenderHierarchy() override;

public:
    virtual void LodUpdate(float distance) {};

    virtual bool ReceivedDamageEvent(float damage, WeaponType wType);
    virtual void ReceivedDamageAnimation();
    bool IsDestroyed() override { return hitPoint <= 0; }
    virtual void DestructionEvent() override;
    
    void UpdateLight() override;
};