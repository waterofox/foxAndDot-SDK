#include "../include/foxAndDot-SDK/Components/Multy_Component.h"

void Multy_Component::update_resource(const Type_Res&){}

void Multy_Component::on_intersection(Scene_Component* other)
{
	for (auto& comp : components)
	{
		if (comp.second.first->intersection)
		{
			comp.second.first->on_intersection(other);
		}
	}
}


void Multy_Component::update()
{
	for (int i = 0; i < update_order.size(); ++i)
	{
		Scene_Component* comp = update_order[i];
		if (comp->updatable)
		{
			comp->update();
		}
	}
}

void Multy_Component::set_update_order(const std::string& name, const int& update_order)
{
	auto comp = components.find(name);
	if (comp == components.end())
	{
		printf("Multy_Component ERROR: Component <%s> isn't a part of multy-component <%s>. NULLPTR returns.\n", name.data(), get_name().data());
		return;
	}

	this->update_order.erase(this->update_order.begin() + comp->second.second);
	this->update_order.insert(this->update_order.begin() + update_order, comp->second.first);
	comp->second.second = update_order;
}

void Multy_Component::add(Scene_Component* comp, const int& update_order)
{
	int correct_order = update_order;

	if (update_order <= 0)
	{
		correct_order = 0;
	}
	else if (update_order >= this->update_order.size())
	{
		components[comp->get_name()] = { comp,int(this->update_order.size()) };
		this->update_order.push_back(comp);
		return;
	}

	components[comp->get_name()] = { comp,correct_order};
	this->update_order.insert(this->update_order.begin() + correct_order, comp);
}

const Scene_Component* const  Multy_Component::get(const std::string& name) const
{
	auto comp = components.find(name);
	if (comp != components.end())
	{
		return comp->second.first;
	}
	printf("Multy_Component ERROR: Component <%s> isn't a part of multy-component <%s>. NULLPTR returns.\n", name.data(), get_name().data());
	return nullptr;
}

Scene_Component* const  Multy_Component::get(const std::string& name)
{
	auto comp = components.find(name);
	if (comp != components.end())
	{
		return comp->second.first;
	}
	printf("Multy_Component ERROR: Component <%s> isn't a part of multy-component <%s>. NULLPTR returns.\n", name.data(), get_name().data());
	return nullptr;
}
