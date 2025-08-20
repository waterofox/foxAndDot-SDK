#include "Core.h"
Resource_Manager::Resource_Manager() {}
Resource_Manager::~Resource_Manager() {}
void Resource_Manager::update_resource(Scene_Component* component)
{
	switch (component->type_of_resource)
	{
	case resource_type::no_resource: { return; } break;
	case resource_type::texture: 
	{
		try
		{
			auto texture = texture_library.find(component->resource);
			if (texture != texture_library.end())
			{
				component->update_resource(&(*texture).second);
			}
			else { throw std::runtime_error(ERROR(ERESMAN, "texuture <" + std::to_string(component->resource) + "> does not exist in library")); }
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl; assert(false);
		}
	} break;
	case resource_type::font: 
	{
		try
		{
			auto font = font_library.find(component->resource);
			if (font != font_library.end())
			{
				component->update_resource(&(*font).second);
			}
			else { throw std::runtime_error(ERROR(ERESMAN, "font <" + std::to_string(component->resource) + "> does not exist in library")); }
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl; assert(false);
		}
	} break;
	default:
		break;
	}
}

void Resource_Manager::add_texture(const std::string& texture_url, const int& id)
{
	assert(texture_library[id].loadFromFile(texture_url));
}
void Resource_Manager::add_font(const std::string& font_url, const int& id)
{
	assert(font_library[id].openFromFile(font_url));
}

sf::Texture& Resource_Manager::texture(const int& id)
{
	try
	{
		auto texture = texture_library.find(id);
		if (texture != texture_library.end())
		{
			return texture_library[id];
		}
		else { throw std::runtime_error(ERROR(ERESMAN, "texuture <" + std::to_string(id) + "> does not exist in library")); }
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl; assert(false);
	}
}
sf::Font& Resource_Manager::font(const int& id)
{
	try
	{
		auto font = font_library.find(id);
		if (font != font_library.end())
		{
			return font_library[id];
		}
		else { throw std::runtime_error(ERROR(ERESMAN, "font <" + std::to_string(id) + "> does not exist in library")); }
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl; assert(false);
	}
}

void Resource_Manager::clear_libraries()
{
	if (!texture_library.empty()) { texture_library.clear(); }
	if (!font_library.empty()) { font_library.clear(); }
}