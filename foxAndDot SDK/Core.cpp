#include "Core.h"
Core::Core() {}
Core::~Core(){}

const sf::Time& Core::get_delta_time() { return this->delta_time; }

sf::View& Core::get_camera()
{
	return this->camera;
}

void Core::set_camera_mod(const camera_settings& mod)
{
	camera_mod = mod;
}

void Core::set_camera_target(const std::string& name_of_target)
{
	camera_target = name_of_target;
}

void Core::set_process_events_function(const process_events_function& function) { this->process_events = function; }

Drawable_Entity* Core::get_entity(const std::string& name)
{
	try
	{
		for (int i = 0; i < scene.size(); ++i)
		{
			lay_type& lay = scene[i];
			auto entity = lay.find(name);
			if (entity != lay.end()) { return (*entity).second; }
		}
		throw std::runtime_error (ERROR(ECORE,"target <" + "> does not exist"));
	}
	catch (const std::exception& err){ std::cout << err.what() << std::endl; this->close();}
}
Drawable_Entity* Core::get_entity(const std::string& name, const int& lay)
{
	try
	{
		lay_type& our_lay = scene[lay];
		auto entity = our_lay.find(name);
		if (entity != our_lay.end()) { return (*entity).second; }
		else { throw std::runtime_error(ERROR(ECORE, "target <" + "> does not exist")); }
	}
	catch (const std::exception& err) { std::cout << err.what() << std::endl; this->close(); }
}

void Core::run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title,const sf::State& state)
{
	sf::Clock clock;
	clock.start();
	this->create(sf::VideoMode({ window_width,window_height }), window_title,state);
	while (this->isOpen())
	{
		this->delta_time = clock.restart();
		try{
			process_events == nullptr ? throw std::runtime_error(ERROR(ECORE, "process events function does not exist")) : process_events(this);
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

void Core::emit_signal(const int& signal_id, Drawable_Entity*& sender)
{
	auto connection = connections.find(signal_id);
	try {
		if (connection == connections.end()) { throw std::runtime_error(ERROR(ECORE, "connection does not exist")); }
		else 
		{
			signals_container new_container;
			new_container.first = (*connection).second;
			new_container.second = std::pair<Drawable_Entity*, Drawable_Entity*>(sender, sender);
			signals_queue.push(new_container);
		}
	}
	catch (std::exception& err) { std::cout << err.what() << std::endl; this->close(); }
}
void Core::emit_signal(const int& signal_id, Drawable_Entity*& sender_A, Drawable_Entity*& sender_B) 
{
	auto connection = connections.find(signal_id);
	try {
		if (connection == connections.end()) { throw std::runtime_error(ERROR(ECORE, "connection does not exist")); }
		else
		{
			signals_container new_container;
			new_container.first = (*connection).second;
			new_container.second = std::pair<Drawable_Entity*, Drawable_Entity*>(sender_A, sender_B);
			signals_queue.push(new_container);
		}
	}
	catch (std::exception& err) { std::cout << err.what() << std::endl; this->close(); }
}

void Core::process_signals() 
{
	while (!signals_queue.empty())
	{
		signals_container front_container = signals_queue.front();
		signals_queue.pop();
		switch (front_container.first.index())
		{
		case 0: 
		{
			slot_type slot = std::get<slot_type>(front_container.first);
			slot(this,front_container.second.first);
		}break;
		case 1:
		{
			dual_slot_type slot = std::get<dual_slot_type>(front_container.first);
			slot(this, front_container.second.first, front_container.second.second);
		}break;
		default:
			break;
		}
	}
}
void Core::process_intersections_and_collisions()
{
	for (int i = 0; i <  scene.size(); ++i)
	{
		Core::lay_type& actual_lay = scene[i];
		for (auto& elementA : actual_lay)
		{
			for (auto& elementB : actual_lay)
			{
				if (&elementA == &elementB) { continue; }
				if (elementA.second->get_entity_local_bounds().findIntersection(elementB.second->get_entity_local_bounds()))
				{
					if (elementA.second->on_intersection != nullptr)
					{
						Core::signals_container container;
						container.first = elementA.second->on_intersection;
						container.second = std::pair<Drawable_Entity*, Drawable_Entity*>(elementA.second, elementB.second);

						signals_queue.push(container);
					}
				}
			}
		}
	}
}

void Core::update_camera() 
{
	switch (camera_mod)
	{
	case Core::dynamic_camera: 
	{ 
		
		Drawable_Entity* target = this->get_entity(this->camera_target);
		sf::Drawable* casted_target = target->asDrawable();
		try
		{
			sf::Sprite* entity = dynamic_cast<sf::Sprite*>(casted_target);
			this->camera.setCenter(entity->getPosition());
			this->setView(camera);
		}
		catch (const std::bad_cast& err)
		{
			std::cout << err.what() << std::endl; 
			std::cout << ERROR(ECORE, "failed cast from your custom object");
			this->close();
		}

	}break;
	case Core::static_camera: 
	{
		this->setView(camera);
	}break;
	default:
		break;
	}
}

void Core::update()
{
	process_signals();
	update_camera();

	for (int i = 0; i < scene.size(); ++i)
	{
		lay_type& lay = scene[i];
		if (!lay.empty())
		{
			for (auto& element : lay)
			{
				Drawable_Entity*& entity = element.second;
				if (entity->is_updateble()){entity->update(this);}
			}
		}
	}
	process_intersections_and_collisions();
}

void Core::render()
{
	this->clear();
	
	for (int i = 0; i < scene.size(); ++i)
	{
		lay_type& lay = scene[i];
		if (!lay.empty())
		{
			for (auto& element : lay)
			{
				Drawable_Entity*& entity = element.second;
				if (entity->is_visible())
				{
					sf::Vector2f camera_position = camera.getCenter();
					sf::Vector2f camera_size = camera.getSize();

					camera_position -= sf::Vector2f(camera_size.x / 2, camera_size.y / 2);

					sf::FloatRect camera_bounds(camera_position, camera_size);

					if (camera_bounds.findIntersection(entity->get_entity_global_bounds()))
					{
						sf::Drawable* drawable_entity = entity->asDrawable();
						this->draw(*drawable_entity);
					}
				}
			}
		}
	}


	this->display();
}
