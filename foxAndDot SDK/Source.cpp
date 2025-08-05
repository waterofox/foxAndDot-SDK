#include "Core.h"
#define speed 150

class myText : public Drawable_Entity, public sf::Text
{	
public:
	myText(const sf::Font& font, std::string mes) : sf::Text(font, mes) {}

	sf::Drawable* asDrawable() override { return this; }
	void update(Core* the_core) override 
	{
		Entity* target_entity = static_cast<Entity*>(the_core->get_entity("player"));
		Entity& player = (*target_entity);

		std::string message = "player position: <x: " + std::to_string(player.getPosition().x) + " y: " + std::to_string(player.getPosition().y) + ">";
		this->setString(message);
	}
	sf::FloatRect get_entity_local_bounds() { return this->getLocalBounds(); }
	sf::FloatRect get_entity_global_bounds() { return this->getGlobalBounds(); }
};


void process_event(Core* the_core)
{
	const auto onClose = [the_core](const sf::Event::Closed&){
		(*the_core).close();};
	const auto onKeyPressed = [the_core](const sf::Event::KeyPressed& keyPressed) {
		Entity* entity = static_cast<Entity*>(the_core->get_entity("player"));
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
		Entity* entity = static_cast<Entity*>(the_core->get_entity("player"));
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
void stiker_script(Core* the_core, Entity* ent)
{
	Entity* player = static_cast<Entity*>(the_core->get_entity("player"));
	ent->setPosition(player->get_collision_bounds().position);
	int w = player->get_collision_bounds().size.x;
	int h = player->get_collision_bounds().size.y;
	ent->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(w, h)));

}


int main()
{

	sf::Font font;
	font.openFromFile("C:\\Users\\Пользователь\\Desktop\\TDAText\\TDAText.ttf");
	myText text(font, "text");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(24);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("C:\\Users\\Пользователь\\Downloads\\d1e68f5909522180.png");
	
	Entity player(playerTexture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(128, 128)));
	player.setPosition(sf::Vector2f(0, 0));

	player.add_property("move_W", false);
	player.add_property("move_D", false);
	player.add_property("move_S", false);
	player.add_property("move_A", false);
	
	player.set_colliding(true);
	player.get_collision_bounds() = sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(64,64));
	player.set_collision_padding(sf::Vector2f(32, 32));

	player.set_script(test_script);

	sf::Texture col;
	col.loadFromFile("C:\\Users\\Пользователь\\Downloads\\redHouse11.png");

	Entity col_e(col, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(0, 0)));

	col_e.set_script(stiker_script);

	sf::Texture box;
	box.setRepeated(true);
	box.loadFromFile("C:\\Users\\Пользователь\\Downloads\\roadHV.png");

	Entity box_e(box, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(128,128)));
	box_e.set_colliding(true);
	box_e.get_collision_bounds() = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(128, 128));

	box_e.setPosition(sf::Vector2f(300,200));



	Core::scene_type scene;
	scene.push_back(Core::lay_type());
	scene.push_back(Core::lay_type());
	scene[0]["player"] = &player;
	scene[0]["box"] = &box_e;
	scene[1]["stiker"] = &col_e;

	scene[0]["player_info"] = &text;
	
	Core the_core;
	the_core.scene = scene;

	the_core.set_process_events_function(process_event);

	the_core.set_camera_mod(Core::camera_settings::static_camera);
	//the_core.set_camera_target("player");

	the_core.run(640,480,"test",sf::State::Windowed);
}