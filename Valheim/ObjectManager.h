#pragma once
#define MINIMUM_FEATURE_COUNT 250

template<typename T>
void ListEraser(std::list<T*>& list) {
	list.erase(
		std::remove_if(
			list.begin(),
			list.end(),
			[](T* element) {
				if (element->IsDestroyed()) 
				{
					element->DestructionEvent();
					return true;
				}
				else return false;
			}
		),
		list.end()
	);
}

class ObjectManager
{
private:
	list<class Prototype*>		objects;
	list<class Prototype*>		instancingObjects;
	list<class ItemProto*>		items;
	//list<class StructureProto*>	structures;

	//class ItemProto*		stoneAxe[5];
	//class ItemProto*		woodpile[5];
	//class ItemProto*		stone[5];
	//class ItemProto*		woodShield[5];
	//class ItemProto*		leather[5];
	//class ItemProto*      elderTrophy[5];
	//class ItemProto*      fineWood[5];
	class FeatureProto*		shipwreck;	// 난파선

	int featureCount{ 0 };
	Vector3* 				startingPosition{ nullptr };          // 플레이어 시작 위치

public:
	ObjectManager();
	~ObjectManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void	RefractionRender();
	void    RenderHierarchy();

	void	GenerateTree();
	void	GenerateInstanceGrass();

	void	AddObject(Prototype* object);
	void    AddInstancingObject(Prototype* object);
	void	AddItem(ItemProto* item);

	list<Prototype*>	GetObjects() { return objects; }
	list<Collider*>		GetColliders();
	Vector3				GetStartingPosition() { return Vector3(startingPosition->x, startingPosition->y, startingPosition->z); }

};

