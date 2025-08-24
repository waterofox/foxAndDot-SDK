#include "Core.h"
#define speed 250


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

enum textures
{
	player_front_texutre = 0,
	player_back_texture = 1,
	player_left_side_texture = 2,
	player_right_side_texture = 3,

	terrain_texture = 4,
	fire_texture = 5,
	ash_texture = 6,
};


void controller_script(Core* the_core,Entity* ent)
{
	
	Animated_Entity* casted_entity = static_cast<Animated_Entity*>(ent);
	Animated_Entity& player = *casted_entity;
	
	sf::Vector2f movement(0, 0);

	if (Bool(player["move_W"]))
	{
		movement.y -= speed * the_core->get_delta_time().asSeconds();
		player.get_resource() = player_back_texture;
	}
	if (Bool(player["move_S"]))
	{
		movement.y += speed * the_core->get_delta_time().asSeconds();
		player.get_resource() = player_front_texutre;
	}
	if (Bool(player["move_D"]))
	{
		movement.x += speed * the_core->get_delta_time().asSeconds();
		player.get_resource() = player_right_side_texture;
	}
	if (Bool(player["move_A"]))
	{
		movement.x -= speed * the_core->get_delta_time().asSeconds();
		player.get_resource() = player_left_side_texture;
	}

	if (movement.x != 0 or movement.y != 0)
	{
		player.play_animation();
	}
	else
	{
		player.pause_animation();
		player.current_frame = 1;
	}

	player.move(movement);
}

int main()
{
	Core the_core;


	//PLAYER
	//init player
	Animated_Entity player_entity(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 64)));
	player_entity.setPosition(sf::Vector2f(256, 256));
	player_entity.setScale(sf::Vector2f(4, 4));

	player_entity.add_property("move_W", false);
	player_entity.add_property("move_A", false);
	player_entity.add_property("move_S", false);
	player_entity.add_property("move_D", false);

	//texturing
	Core::resource_manager.add_texture("Game\\playerFrontWalk.png", player_front_texutre);
	Core::resource_manager.add_texture("Game\\playerBackWalk.png", player_back_texture);
	Core::resource_manager.add_texture("Game\\playerSideLeftWalk.png", player_left_side_texture);
	Core::resource_manager.add_texture("Game\\playerSideRightWalk.png", player_right_side_texture);

	player_entity.get_type_of_resource() = Resource_Manager::resource_type::texture;
	player_entity.get_resource() = player_front_texutre;

	//animation
	player_entity.current_frame = 1;
	player_entity.frame_per_seconds = 6;
	player_entity.frame_count = 4;
	
	player_entity.pause_animation();
	
	player_entity.set_colliding(true);
	player_entity.set_collision_padding(sf::Vector2f(96, 112));
	player_entity.get_collision_bounds() = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(64, 128));

	//scripting
	player_entity.set_script(controller_script);

	//AREA
	Entity field(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(320, 320)));
	field.setPosition(sf::Vector2f(0, 0));
	field.setScale(sf::Vector2f(4, 4));

	Core::resource_manager.add_texture("Game\\field.png", terrain_texture);
	Core::resource_manager.texture(terrain_texture).setRepeated(true);

	field.get_type_of_resource() = Resource_Manager::resource_type::texture;
	field.get_resource() = terrain_texture;

	//----------------------------------------------------------------------------------------
	Animated_Entity fire(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(64,64)));
	Core::resource_manager.add_texture("Game\\fire.png", fire_texture);

	fire.setScale(sf::Vector2f(4,4));
	fire.setPosition(sf::Vector2f(512, 512));

	fire.frame_per_seconds = 12;
	fire.frame_count = 6;
	fire.play_animation();

	fire.get_resource() = fire_texture;
	fire.get_type_of_resource() = Resource_Manager::resource_type::texture;
	//----------------------------------------------------------------------------------------
	Animated_Entity Ash(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 64)));
	Core::resource_manager.add_texture("Game\\ahIdle.png", ash_texture);

	Ash.get_resource() = ash_texture;
	Ash.get_type_of_resource() = Resource_Manager::resource_type::texture;
	
	Ash.setScale(sf::Vector2f(4, 4));
	Ash.setPosition(sf::Vector2f(512, 412));

	Ash.frame_per_seconds = 12;
	Ash.frame_count = 10;
	Ash.play_animation();
	//----------------------------------------------------------------------------------------
	Collision_Area col(sf::FloatRect(sf::Vector2f(576, 412), sf::Vector2f(128, 200)));
	col.set_visble(true);

	//init scene
	Core::lay_type lay0; lay0["field"] = &field;
	Core::lay_type lay1; lay1["Ash"] = &Ash;
	Core::lay_type lay2; lay2["fire"] = &fire;
	Core::lay_type lay3; lay3["player"] = &player_entity; lay3["col1"] = &col;

	the_core.scene_name = "demo";

	the_core.scene.push_back(lay0);
	the_core.scene.push_back(lay1);
	the_core.scene.push_back(lay2);
	the_core.scene.push_back(lay3);
	
	//camera
	the_core.set_camera_mod(Core::camera_settings::dynamic_camera);
	the_core.set_camera_target("player");

	//start game
	the_core.set_process_events_function(process_event);
	the_core.run(640,480,"Fox&Dot SDK Demo",sf::State::Windowed);
	
}


