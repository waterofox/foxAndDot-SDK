#include "../include/foxAndDot-SDK/Core.h"
#include "../include/foxAndDot-SDK/Components/Scene_Component.h"

//ERRORS
#define ECORE std::string("CORE ERROR: ")
#define ERROR(error_location,error_message) error_location + error_message

void Core::change_scene(Scene* new_Scene)
{
	if (changin_scene)
	{
		printf("CORE ERROR: More than one scene change per tick\n");
		return;
	}
	else
	{
		scene_buffer = new_Scene;
		changin_scene = true;
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
	this->the_core = this;
	
}
void Core::run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title,\
	const unsigned long& framerate_limit, const sf::State& state)
{
	this->game_cycle_clock.start();
	this->create(sf::VideoMode({ window_width,window_height }), window_title,state);
	this->setFramerateLimit(framerate_limit);
	while (this->isOpen())
	{

		//scene
		if(changin_scene)
		{
			actual_scene = scene_buffer;
			scene_buffer = nullptr;
			changin_scene = false;
		}

		this->delta_time = this->game_cycle_clock.restart();
		try{
			 event_handler == nullptr ? throw std::runtime_error(ERROR(ECORE, "process events function does not exist")) : (*event_handler)();
		}
		catch (std::exception& err) { std::cout << err.what() << std::endl; this->close(); }

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
		for (auto& elementB : actual_scene->scene_data)
		{
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
		if (comp->is_updateble()) { comp->update(); }
		resource_manager.update_resource(comp);
	}
	process_intersections_and_collisions();

	handle_slots();
}

void Core::render()
{
	this->clear(sf::Color::Black);

	for (auto& view : views)
	{
		this->setView(view.second);
		actual_scene->render(view.second);
	}

	this->display();
}
