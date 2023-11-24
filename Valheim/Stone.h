#include "ItemProto.h"
class Stone : public MaterialProto
{
private:
	friend class ItemProto;

private:
	Stone();
	~Stone();

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render() override;
	void RenderHierarchy() override;

	wstring GetExplain() override;

	//bool IsDestroyed() override;
	//void DestructionEvent() override;

	void Use() override;
};

