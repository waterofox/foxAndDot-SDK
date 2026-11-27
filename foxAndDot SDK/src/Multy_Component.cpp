#include "../include/foxAndDot-SDK/Components/Multy_Component.h"

void Multy_Component::update_resource(const Type_Res&)
{
}

void Multy_Component::update()
{
	for (auto& comp : components)
	{
		if (comp.second->updatable) 
		{
			comp.second->update();
		}
	}
}

void Multy_Component::add(Scene_Component* comp)
{
	components[comp->get_name()] = comp;
}

const Scene_Component* const  Multy_Component::get(const std::string& name) const
{
	auto comp = components.find(name);
	if (comp != components.end())
	{
		return comp->second;
	}
	printf("Multy_Component ERROR: Component <%s> isn't a part of multy-component <%s>. NULLPTR returns.\n", name.data(), get_name().data());
	return nullptr;
}

Scene_Component* const  Multy_Component::get(const std::string& name)
{
	auto comp = components.find(name);
	if (comp != components.end())
	{
		return comp->second;
	}
	printf("Multy_Component ERROR: Component <%s> isn't a part of multy-component <%s>. NULLPTR returns.\n", name.data(), get_name().data());
	return nullptr;
}
