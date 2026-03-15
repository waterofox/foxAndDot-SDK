
#include "include/foxAndDot-SDK/Core.h"
#include "include/foxAndDot-SDK/Tools/Script.h"
#include "include/foxAndDot-SDK/Components/Animated_Entity.h"
#include "include/foxAndDot-SDK/Components/Visualized_Collider.h"

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
		sf::View& camera = *Core::the_core->get_view("main");

		if (this_entity->getPosition().x >= camera.getCenter().x + camera.getSize().x / 2)
		{
			this_entity->setPosition(sf::Vector2f(camera.getCenter().x - camera.getSize().x / 2 - 20, 0));
		}
		
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

	Animated_Entity ent(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 30)));
	ent.set_resource_and_type(frisk, Resource_Types::Texture);
	ent.set_colliding(true);
	ent.set_collider_margin(sf::Vector2f(0, 0));
	ent.set_collision_size(sf::Vector2f(20, 30));
	ent.setPosition(sf::Vector2f(-100, 0));
	ent.set_name("ent");

	ent.current_frame = 0;
	ent.frame_count = 4;
	ent.frame_per_seconds = 6;

	ent.play_animation();

	meScrpt scrt;
	ent.set_script(&scrt);
	

	Visualized_Collider col;
	col.set_bounds(sf::FloatRect(sf::Vector2f(80, 0), sf::Vector2f(1, 20)));

	Entity obst(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 20)));
	obst.set_resource_and_type(floor_t, Resource_Types::Texture);
	obst.set_colliding(false);
	obst.set_collider_margin(sf::Vector2f(0, 0));
	obst.set_collision_size(sf::Vector2f(20, 20));
	obst.setPosition(sf::Vector2f(100, 0));
	obst.set_name("obst");


	sf::View camera;
	camera.setCenter(sf::Vector2f(0, 0));
	camera.setSize(sf::Vector2f(640, 480));
	camera.zoom(0.5);

	core.add_view("main", camera);

	Scene scene(2);

	scene.add(&ent, 0);
	scene.add(&obst, 0);
	scene.add(&col, 1);

	core.change_scene(&scene);

	evhandler handler;
	core.set_event_handler(&handler);

	core.run(640, 480, "test", 120, sf::State::Windowed);



	return 0;
}
