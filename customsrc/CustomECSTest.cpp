#include <unordered_map>
#include <typeindex>

#include "WinMain.h"
#include "../customlib/Pos.h"
#include "../customlib/DebugTools.h"
#include "../customlib/FadeBox.h"
#include "../customsrc/Scene.h"

extern Scene* currentScene_p;
extern Time gameTime;

struct Entity
{
	size_t id;

	bool operator==(const Entity& other) const
	{
		return id == other.id;
	}
}; //comp

namespace std
{
	template <>
	struct hash<Entity> {
		size_t operator()(const Entity& e) const
			//required for the hash. as a replacement of left hand side of the map. (replacing int, and string)
		{
			return hash<size_t>()(e.id);
		}
	};
}

struct Transform { float x, y; }; //comp


struct IComponentArray {
	virtual ~IComponentArray() = default;
};

template <typename T>
class ComponentArray : public IComponentArray
{
	std::unordered_map<Entity, T> data; //each contains pair of entity and that one type of component.

public:
	void Add(Entity e, const T& component)
	{
		data[e] = component;
	}

	T& Get(Entity e)
	{
		return data.at(e);
	}

	bool Has(Entity e, const T& component)
	{
		return data.find(e) != data.end();
	}
};

struct Registry
{
private:
	std::unordered_map<std::type_index, IComponentArray*> components; //pointers map
public:
	template<typename T>
	ComponentArray<T>& GetArray()
	{
		auto typeIndex = std::type_index(typeid(T));
		if (!components.count(typeIndex)) //add if doesn't exist
		{
			components[typeIndex] = new ComponentArray<T>();
		}
		return *static_cast<ComponentArray<T>*>(components[typeIndex]);
		//Get IComponentArray
		//Cast to ComponentArray from IComponentArray pointer
		//Then, dereference to get the ampersand
	}

	template<typename T>
	void Query()
	{

	}

	~Registry()
	{

	}
};

Registry registry;//test

void PhysicsSystem(Registry& reg)
{

}

void GameInit()
{
	Entity playerE = { 1 };
	currentScene_p = new MainMenuScene();
	auto& transforms = registry.GetArray<Transform>();
	transforms.Add(playerE, Transform{});
}

void GameUpdate()
{
	gameTime.Update();
	currentScene_p->Update();
	//reg.GetArray<Transform>();

	//SYSTEMS
}

void GameDraw()
{
	currentScene_p->Render();
	//
	FadeBox fadebox;
	fadebox.Render();
	//
	DisplayCross();
}

void GameExit()
{
	delete currentScene_p;
}