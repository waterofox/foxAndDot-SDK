#include "Core.h"
void process_event(Core* the_core)
{
	const auto onClose = [the_core](const sf::Event::Closed&){
		(*the_core).close();};
	the_core->handleEvents(onClose);
}

void test_script(Core* the_core,Entity* ent)
{
	Entity& test = *ent;
	test.move(sf::Vector2f(10 * the_core->get_delta_time().asSeconds(), 0));
}

int main()
{
	Core theCore;
	theCore.set_process_events_function(process_event);

	sf::Texture texture;
	texture.loadFromFile("C:/Users/Пользователь/Downloads/d1e68f5909522180.png");

	Entity test(texture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(30, 30)));
	test.add_property("test", "jopa");
	std::cout << String(test["test"]);
	test.set_script(test_script);

	Core::scene_type scene;
	scene.push_back(Core::lay_type());
	scene[0].insert(std::pair<std::string, Drawable_Entity*>("ent", &test));

	theCore.scene = scene;


	theCore.run(300, 300, "test", sf::State::Windowed);
}