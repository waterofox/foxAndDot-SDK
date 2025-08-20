#include "Core.h"
#define speed 150


void process_event(Core* the_core)
{
	const auto onClose = [the_core](const sf::Event::Closed&){
		(*the_core).close();};
	const auto onKeyPressed = [the_core](const sf::Event::KeyPressed& keyPressed) {
		Entity* entity = static_cast<Entity*>(the_core->get_component("player"));
		Entity& player = (*entity);
		
		switch (keyPressed.scancode)
		{
		case sf::Keyboard::Scancode::W: { player["move_W"] = true; }break;
		case sf::Keyboard::Scancode::D: { player["move_D"] = true; }break;
		case sf::Keyboard::Scancode::S: { player["move_S"] = true; }break;
		case sf::Keyboard::Scancode::A: { player["move_A"] = true; }break;
		default:
			break;
		}

		};
	const auto onKeyReleased = [the_core](const sf::Event::KeyReleased& keyReleased) {
		Entity* entity = static_cast<Entity*>(the_core->get_component("player"));
		Entity& player = (*entity);

		switch (keyReleased.scancode)
		{
		case sf::Keyboard::Scancode::W: { player["move_W"] = false; }break;
		case sf::Keyboard::Scancode::D: { player["move_D"] = false; }break;
		case sf::Keyboard::Scancode::S: { player["move_S"] = false; }break;
		case sf::Keyboard::Scancode::A: { player["move_A"] = false; }break;
		default:
			break;
		}

		};
	the_core->handleEvents(onClose,onKeyPressed,onKeyReleased);
}




void test_script(Core* the_core,Entity* ent)
{
	
	Entity& player = (*ent);
	
	sf::Vector2f movement(0, 0);

	if (Bool(player["move_W"]))
	{
		movement.y -= speed * the_core->get_delta_time().asSeconds();
	}
	if (Bool(player["move_D"]))
	{
		movement.x += speed * the_core->get_delta_time().asSeconds();
	}
	if (Bool(player["move_S"]))
	{
		movement.y += speed * the_core->get_delta_time().asSeconds();
	}
	if (Bool(player["move_A"]))
	{
		movement.x -= speed * the_core->get_delta_time().asSeconds();
	}

	player.move(movement);
}

enum textures
{
	player_texutre = 0,
};

int main()
{
	Core the_core;

	Core::resource_manager.add_texture("D:\\Смешной контент\\c096462cff06c06b.png", player_texutre);

	Entity player_entity(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 64)));
	player_entity.setPosition(sf::Vector2f(64, 64));

	player_entity.get_type_of_resource() = Resource_Manager::resource_type::texture;
	player_entity.get_resource() = player_texutre;

	player_entity.set_script(test_script);

	player_entity.add_property("move_W", false);
	player_entity.add_property("move_A", false);
	player_entity.add_property("move_S", false);
	player_entity.add_property("move_D", false);

	Core::lay_type lay; lay["player"] = &player_entity;
	the_core.scene_name = "test";
	the_core.scene.push_back(lay);
	
	the_core.set_process_events_function(process_event);

	the_core.run(400,400,"resource manager test",sf::State::Windowed);
	
}