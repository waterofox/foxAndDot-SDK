#include "include/foxAndDot-SDK/Core.h"
#include "include/foxAndDot-SDK/Components/Animated_Entity.h"
#include "include/foxAndDot-SDK/Components/fAD_Sprite.h"
#include "include/foxAndDot-SDK/Components/fAD_RectangleShape.h"
#include "include/foxAndDot-SDK/Tools/fAD_Event_Handler.h"

#define PROJECTNAME "$(ProjectName)"

class Event_Listner
{
	
	void on_key_pressed(const sf::Keyboard::Scancode& key)
	{
		std::cout << "key_pressed\n";
	}
	void on_key_released(const sf::Keyboard::Scancode& key)
	{
		std::cout << "key_released\n";
	}

	void other_events(const std::optional<sf::Event>& evnt)
	{
		if (evnt->is<sf::Event::MouseMoved>())
		{
			sf::Vector2i pos = evnt->getIf<sf::Event::MouseMoved>()->position;
			std::cout << "mouse\n";
			std::cout << pos.x << ' ' << pos.y;
		}
	}

public:
	Event_Listner()
	{
		on_key_released_slot.reassign(&Event_Listner::on_key_released, this);
		on_key_pressed_slot.reassign(&Event_Listner::on_key_pressed, this);
		other_events_slot.reassign(&Event_Listner::other_events, this);

		connect(&fAD_Event_Handler::key_pressed, &this->on_key_pressed_slot);
		connect(&fAD_Event_Handler::key_released, &this->on_key_released_slot);
		connect(&fAD_Event_Handler::render_window_event, &this->other_events_slot);
	}

	Slot<std::optional<sf::Event>, Event_Listner> other_events_slot;
	Slot<sf::Keyboard::Scancode, Event_Listner> on_key_pressed_slot;
	Slot<sf::Keyboard::Scancode, Event_Listner> on_key_released_slot;

};

int main()
{
	Core the_core;
	Scene scene;
	fAD_Event_Handler evnt_handler;

	Core::resource_manager.add_texture("C:\\Users\\foxsh\\Downloads\\dragon.png", 0);

	Animated_Entity ent = Animated_Entity(sf::Vector2i(32, 32), 0);
	ent.frame_count = 3;
	ent.frame_per_seconds = 24;
	ent.current_frame = 0;
	ent.play_animation();

	Animated_Entity ent_2 = Animated_Entity(ent);
	
	ent_2.frame_per_seconds = 2;
	ent = ent_2;

	fAD_Sprite spr;
	fAD_Sprite srp_2 = fAD_Sprite(sf::Vector2i(32, 32));
	
	spr = srp_2;
	
	spr.set_resource(0);

	fAD_RectangleShape sh = fAD_RectangleShape(sf::Vector2f(300,300));
	sh.setFillColor(sf::Color::Red);

	fAD_RectangleShape rect2;
	sh.setFillColor(sf::Color::Green);
	rect2 = sh;
	

	scene.add_new_lay();
	scene.add(&rect2, 0);

	the_core.add_view("main", sf::View(rect2.getGlobalBounds().getCenter(), sf::Vector2f(600, 600)));

	the_core.change_scene(&scene);
	the_core.set_event_handler(&evnt_handler);
	the_core.get_window().setVerticalSyncEnabled(true);
	

	the_core.run(600, 600, PROJECTNAME, 120, sf::State::Windowed);
}