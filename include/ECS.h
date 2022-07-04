#pragma once

#include "3D Space.h"

class Entity;
class Component;

using ComponentTypeID = std::size_t;

inline ComponentTypeID GetUniqueComponentTypeID() {
	static ComponentTypeID lastID = 0;
	return lastID++;
}

template<typename T>
inline ComponentTypeID GetComponentTypeID() {
	static_assert(std::is_base_of<Component, T>::value, "Type is not based on component");
	static const ComponentTypeID typeID = GetUniqueComponentTypeID();
	return typeID;
}

constexpr std::size_t ECS_MAX_ENTITIES = 5000;
constexpr std::size_t ECS_MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<ECS_MAX_ENTITIES>;
using ComponentList = std::array<Component*, ECS_MAX_COMPONENTS>;

class Entity {
private:
	bool m_isAlive;
	ComponentBitset m_compoBitset;
	ComponentList m_compoList;
	std::vector<std::unique_ptr<Component>> m_components;

public:
	Entity() = default;
	virtual ~Entity() = default;

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args) {
		T* component(new T(std::forward<TArgs>(args)...));
		component->entity = this;
		std::unique_ptr<Component> uptr{ component };
		m_components.emplace_back(std::move(uptr));
		if (component->Init()) {
			m_compoList[GetComponentTypeID<T>()] = component;
			m_compoBitset[GetComponentTypeID<T>()] = true;
			component->entity = this;
			m_isAlive = true;
			return *component;
		}

		return *static_cast<T*>(nullptr);
	}

	template<typename T>
	inline T& GetComponent() const {
		auto ptr(m_compoList[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template<typename T>
	inline bool HasComponent() const {
		return m_compoBitset[GetComponentTypeID<T>()];
	}

	inline bool IsAlive() const {
		return m_isAlive;
	}

	inline void Destroy() {
		m_isAlive = false;
	}
};

class Component {
public:
	Entity* entity{ nullptr };

public:
	Component() = default;
	virtual ~Component() = default;

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
