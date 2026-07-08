#include "../include/foxAndDot-SDK/Core.h"
#include "../include/foxAndDot-SDK/Components/Scene_Component.h"

sf::RenderWindow& Core::get_window()
{
	return this->game_window;
}

void Core::change_scene(Scene* new_Scene)
{
	if (changing_scene)
	{
		printf("CORE ERROR: More than one scene change per tick\n");
		return;
	} 

	else
	{
		scene_buffer = new_Scene;
		changing_scene = true;
	}
}

Scene* Core::get_actual_scene()
{
	if (actual_scene == nullptr)
	{
		printf("CORE WARNING: No scenes are installed. <nullptr> is passed\n");
	}

	return actual_scene;
}

const sf::Time& Core::get_delta_time() { return this->delta_time; }

void Core::set_event_handler(Executable* handler)
{
	this->event_handler = handler;
}

Core::Core()
{
	this->handle_collider_slot.reassign(&Core::handle_collider, this);	
	this->the_core = this;
}

void Core::run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title,\
	const unsigned long& framerate_limit, const sf::State& state)
{
	if (this->game_window.isOpen())
	{
		printf("CORE ERROR: There is already an active window. You cannot start the Core again\n");
	}

	this->game_cycle_clock.start();
	this->game_window.create(sf::VideoMode({ window_width,window_height }), window_title,state);
	this->game_window.setFramerateLimit(framerate_limit);
	while (this->game_window.isOpen())
	{

		//scene
		if(changing_scene)
		{
			Changed_Scene_Package package;
			
			package.old_scene = actual_scene;
			package.new_scene = scene_buffer;

			actual_scene = scene_buffer;
			scene_buffer = nullptr;
			changing_scene = false;	

			this->scene_had_changed.push_args(package);
			this->emit(&scene_had_changed);
		}

		if (actual_scene == nullptr) 
		{
			printf("CORE ERROR: No loaded scene\n");
			this->game_window.close();
			return;
		}

		this->delta_time = this->game_cycle_clock.restart();
		
		if (this->event_handler == nullptr)
		{
			printf("CORE WARNING: The event handler is not defined\n");
		}
		else
		{
			(*this->event_handler)();
		}

		update();
		render();
	}
}


void Core::add_view(const std::string& view_name, const sf::View& view)
{
	if (this->views.find(view_name) != this->views.end())
	{
		printf("CORE ERROR: Overwriting an existing view\n");
		return;
	}
	else
	{
		this->views[view_name] = view;
	}
}

void Core::remove_view(const std::string& view_name)
{
	if (this->views.find(view_name) == this->views.end())
	{
		printf("CORE ERROR: Removing a non-existent view\n");
		return;
	}
	else
	{
		this->views.erase(view_name);
	}
}

sf::View* Core::get_view(const std::string& view_name)
{
	if (this->views.find(view_name) == this->views.end())
	{
		printf("CORE ERROR: Getting a non-existent view\n");
		return nullptr;
	}
	else
	{
		return &this->views[view_name];
	}
}


void Core::handle_collider(const Collider_Args_Package& args)
{
	args.other_comp->on_intersection(args.collider);
}

void Core::handle_slots()
{
	while (!this->emited_queue.empty())
	{
		(*(this->emited_queue).front())();
		emited_queue.pop();
	}
}
void Core::process_intersections_and_collisions()
{
	for (auto& elementA : actual_scene->scene_data)
	{
		if (!elementA.second.component->is_intersection()) { continue; }
		for (auto& elementB : actual_scene->scene_data)
		{
			if (!elementB.second.component->is_intersection()) { continue; }
			if (&elementA == &elementB) { continue; }
			if (elementA.second.component->get_component_bounds().findIntersection(elementB.second.component->get_component_bounds()))
			{
				elementA.second.component->on_intersection(elementB.second.component);
			}
		}
	}
}

void Core::update()
{
	for (auto& element : actual_scene->scene_data)
	{
		Scene_Component*& comp = element.second.component;
		if (comp->is_updatable()) { comp->update(); }
		resource_manager.update_resource(comp);
	}
	process_intersections_and_collisions();

	handle_slots();
}

void Core::render()
{
	this->game_window.clear(sf::Color::Black);

	for (auto& view : views)
	{
		this->game_window.setView(view.second);
		actual_scene->render(view.second);
	}

	this->game_window.display();
}
