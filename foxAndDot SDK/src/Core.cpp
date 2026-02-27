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
	sf::Clock clock;
	clock.start();
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

		this->delta_time = clock.restart();
		try{
			 event_handler == nullptr ? throw std::runtime_error(ERROR(ECORE, "process events function does not exist")) : (*event_handler)();
		}
		catch (std::exception& err) { std::cout << err.what() << std::endl; this->close(); }

		update();
		render();
	}
}

void Core::connect(const int& signal_id, const std::variant<slot_type, dual_slot_type>& slot)
{
	connections[signal_id] = slot;
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

void Core::emit_signal(const int& signal_id, Scene_Component*& sender)
{
	auto connection = connections.find(signal_id);
	try {
		if (connection == connections.end()) { throw std::runtime_error(ERROR(ECORE, "connection does not exist")); }
		else 
		{
			signals_container new_container;
			new_container.first = (*connection).second;
			new_container.second = std::pair<Scene_Component*, Scene_Component*>(sender, sender);
			signals_queue.push(new_container);
		}
	}
	catch (std::exception& err) { std::cout << err.what() << std::endl; this->close(); }
}
void Core::emit_signal(const int& signal_id, Scene_Component*& sender_A, Scene_Component*& sender_B) 
{
	auto connection = connections.find(signal_id);
	try {
		if (connection == connections.end()) { throw std::runtime_error(ERROR(ECORE, "connection does not exist")); }
		else
		{
			signals_container new_container;
			new_container.first = (*connection).second;
			new_container.second = std::pair<Scene_Component*, Scene_Component*>(sender_A, sender_B);
			signals_queue.push(new_container);
		}
	}
	catch (std::exception& err) { std::cout << err.what() << std::endl; this->close(); }
}

void Core::process_signals() 
{
	while (!signals_queue.empty())
	{
		signals_container& front_container = signals_queue.front();
		switch (front_container.first.index())
		{
		case 0: 
		{
			slot_type& slot = std::get<slot_type>(front_container.first);
			slot(this,front_container.second.first);
		}break;
		case 1:
		{
			dual_slot_type& slot = std::get<dual_slot_type>(front_container.first);
			slot(this, front_container.second.first, front_container.second.second);
		}break;
		default:
			break;
		}
		signals_queue.pop();
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
				elementA.second.component->on_intersection(this, elementB.second.component);
			}
		}
	}
}

void Core::update()
{
	process_signals();

	for (auto& element : actual_scene->scene_data)
	{
		Scene_Component*& comp = element.second.component;
		if (comp->is_updateble()) { comp->update(); }
		resource_manager.update_resource(comp);
	}
	process_intersections_and_collisions();
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
