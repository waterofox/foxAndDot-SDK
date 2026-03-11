
#include "include/foxAndDot-SDK/Core.h"
#include "include/foxAndDot-SDK/Tools/Script.h"
#include "include/foxAndDot-SDK/Components/Entity.h"

enum textures
{
	frisk = 0,
	floor_t = 1,
};

#define speed 50

class meScrpt : public Script
{
	void operator()() override
	{
		this_entity->move(sf::Vector2f(speed * Core::the_core->get_delta_time().asSeconds(), 0));
	}
};

class evhandler : public Executable
{
	void operator()() override
	{
		while (const std::optional event = Core::the_core->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				Core::the_core->close();
			}
		}
	}
};

int main()
{
	Core core;
	core.resource_manager.add_texture("resources\\sprites\\frisk\\frisk_front.png", frisk);
	core.resource_manager.add_texture("resources\\sprites\\area\\floor.png", floor_t);

	Entity ent(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 30)));
	ent.set_resource_and_type(frisk, Resource_Manager::texture);
	ent.set_colliding(true);
	ent.set_collider_margin(sf::Vector2f(0, 0));
	ent.set_collision_size(sf::Vector2f(20, 30));
	ent.setPosition(sf::Vector2f(-100, 0));
	ent.set_name("ent");

	meScrpt scrt;
	ent.set_script(&scrt);

	Entity obst(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 20)));
	obst.set_resource_and_type(floor_t, Resource_Manager::texture);
	obst.set_colliding(true);
	obst.set_collider_margin(sf::Vector2f(0, 0));
	obst.set_collision_size(sf::Vector2f(20, 20));
	obst.setPosition(sf::Vector2f(100, 0));
	obst.set_name("obst");

	sf::View camera;
	camera.setCenter(sf::Vector2f(0, 0));
	camera.setSize(sf::Vector2f(640, 480));
	camera.zoom(0.5);

	core.add_view("main", camera);

	Scene scene(1);

	scene.add(&ent, 0);
	scene.add(&obst, 0);

	core.change_scene(&scene);

	evhandler handler;
	core.set_event_handler(&handler);

	core.run(640, 480, "test", 60, sf::State::Windowed);



	return 0;
}
