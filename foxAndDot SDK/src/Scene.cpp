#include "../include/foxAndDot-SDK/Tools/Scene.h"
#include "../include/foxAndDot-SDK/Core.h"

void Scene::render(const sf::View& view)
{
	sf::FloatRect view_bounds(sf::Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2), view.getSize());

	sf::RenderWindow& window = Core::the_core->get_window();
	for (int i = 0; i < this->render_order.size(); ++i)
	{
		for (auto& comp : this->render_order[i])
		{
			if (comp.second->is_visible() and view_bounds.findIntersection(comp.second->get_component_render_bounds()))
			{
				window.draw(*comp.second->as_drawable());
			}
		}
	}
}

void Scene::add(Scene_Component*comp, const int& lay)
{
	if (lay >= this->render_order.size())
	{
		printf("SCENE ERROR: Lay index <%d> out of range\n", lay);
		return;
	}

	if (this->scene_data.find(comp->get_name()) == this->scene_data.end())
	{
		//so all good man
		this->scene_data[comp->get_name()] = Scene::comp_info();
		this->scene_data[comp->get_name()].actual_comp_lay = lay;
		this->scene_data[comp->get_name()].component = comp;

		this->render_order[lay][comp->get_name()] = this->scene_data[comp->get_name()].component;
	}
	else
	{
		std::cout << "SCENE ERROR: Overwriting a component <" << comp->get_name() << ">\n";
	}
}

void Scene::remove(const std::string& component_name)
{
	if (this->scene_data.find(component_name) != this->scene_data.end())
	{
		//so all good man

		this->render_order.erase(this->scene_data[component_name].actual_comp_lay);
		this->scene_data.erase(component_name);
	}
	else
	{
		std::cout << "SCENE ERROR: Deleting a non-existent component <" << component_name << ">\n";
	}
}

void Scene::move_on_lay(const std::string& component_name, const int& lay)
{
	if (lay >= this->render_order.size())
	{
		printf("SCENE ERROR: Lay index <%d> out of range\n", lay);
		return;
	}

	if (this->scene_data.find(component_name) != this->scene_data.end())
	{
		//so all good man

		this->render_order[this->scene_data[component_name].actual_comp_lay].erase(component_name);

		this->scene_data[component_name].actual_comp_lay = lay;
		this->render_order[lay][component_name] = this->scene_data[component_name].component;
	}
	else
	{
		std::cout << "SCENE ERROR: Attempting to move a non-existent component between layers <" << component_name << ">\n";
	}
}

bool Scene::is_on_scene(const std::string& component_name)
{
	if (this->scene_data.find(component_name) != this->scene_data.end())
	{
		return true;
	}
	return false;
}

void Scene::add_new_lay(const int& lay_count)
{
	int last_valid_lay = this->render_order.size();
	
	for (int i = 0; i < lay_count; ++i)
	{
		this->render_order[last_valid_lay] = std::unordered_map<std::string, Scene_Component*>();
		++last_valid_lay;
	}
}

Scene_Component* Scene::operator[](const std::string& component_name)
{
	if (is_on_scene(component_name))
	{
		return this->scene_data[component_name].component;
	}
	else
	{
		std::cout << "SCENE ERROR: Getting a non-existent component <" << component_name << ">\n";
		return nullptr;
	}
}

Scene_Component* Scene::operator[](const char* component_name)
{
	return (*this)[std::string(component_name)];
}

Scene::Scene(const int& lays_count)
{
	for (int i = 0; i < lays_count; ++i)
	{
		this->render_order[i] = std::unordered_map<std::string, Scene_Component*>();
	}
}
