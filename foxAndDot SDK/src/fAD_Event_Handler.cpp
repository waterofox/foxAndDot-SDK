#include "../include/foxAndDot-SDK/Tools/fAD_Event_Handler.h"

#include "../include/foxAndDot-SDK/Core.h"

void fAD_Event_Handler::operator()()
{
	if (game_window == nullptr)
	{
		game_window = &Core::the_core->get_window();
	}

	while (auto evnt = game_window->pollEvent())
	{
		render_window_event.push_args(evnt);
		Core::the_core->emit(&render_window_event);

		if (evnt->is<sf::Event::Closed>()) { game_window->close(); break;}
		else if (evnt->is<sf::Event::KeyPressed>())
		{
			key_pressed.push_args(evnt->getIf<sf::Event::KeyPressed>()->scancode);
			Core::the_core->emit(&key_pressed);
		}
		else if (evnt->is<sf::Event::KeyReleased>())
		{
			key_released.push_args(evnt->getIf<sf::Event::KeyReleased>()->scancode);
			Core::the_core->emit(&key_released);
		}
	}
}
