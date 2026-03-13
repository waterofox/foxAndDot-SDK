#include "../include/foxAndDot-SDK/Core.h"
#include "../include/foxAndDot-SDK/Components/Scene_Component.h"

#define ERESMAN std::string("RESOURCE MANAGER ERROR: ")
#define ERROR(error_location,error_message) error_location + error_message

void Resource_Manager::update_resource(Scene_Component*& component)
{
	if (!component->ready_to_update_resource) 
	{ 
		return; 
	} 

	component->ready_to_update_resource = false; 

	switch (component->type_of_resource)
	{
	case Resource_Types::Undefined: { return; } break;
	case Resource_Types::Texture: 
	{

		auto texture = texture_library.find(component->resource);
		if (texture != texture_library.end())
		{
			component->update_resource(&(*texture).second);
		}
		else 
		{
			printf("RESOURCE MANAGER ERROR: texture <%d> does not exist in library\n",component->resource);
		}
	
	} break;

	case Resource_Types::Font: 
	{
		auto font = font_library.find(component->resource);
		if (font != font_library.end())
		{
			component->update_resource(&(*font).second);
		}
		else
		{
			printf("RESOURCE MANAGER ERROR: font <%d> does not exist in library\n", component->resource);
		}
	} break;
	default:
		break;
	}
}

void Resource_Manager::add_texture(const std::string& texture_url, const int& id)
{
	if (!texture_library[id].loadFromFile(texture_url))
	{
		printf("RESOURCE MANAGER ERROR: texture <%d> does not exist,", id);
		std::cout << texture_url << std::endl;
	}
}
void Resource_Manager::add_font(const std::string& font_url, const int& id)
{
	if (!font_library[id].openFromFile(font_url))
	{
		printf("RESOURCE MANAGER ERROR: font <%d> does not exist,", id);
		std::cout << font_url << std::endl;
	}
}

void Resource_Manager::drop_texture(const int& id)
{
	auto texture = texture_library.find(id);
	if (texture != texture_library.end())
	{
		texture_library.erase(id);
	}
	else
	{
		printf("RESOURCE MANAGER ERROR: texture <%d> does not exist in library\n", id);
	}
}

void Resource_Manager::drop_font(const int& id)
{
	auto font = font_library.find(id);
	if (font != font_library.end())
	{
		font_library.erase(id);
	}
	else
	{
		printf("RESOURCE MANAGER ERROR: font <%d> does not exist in library\n", id);
	}
}

void Resource_Manager::clear_textures_library()
{
	if (!texture_library.empty()) { texture_library.clear(); }
}

void Resource_Manager::clear_fonts_library()
{
	if (!font_library.empty()) { font_library.clear(); }
}

sf::Texture& Resource_Manager::get_texture(const int& id)
{
	auto texture = texture_library.find(id);
	if (texture != texture_library.end())
	{
		return texture_library[id];
	}
	else 
	{ 
		printf("RESOURCE MANAGER WARNING: texture <%d> does not exist in library. An empty texture is returned\n", id);
		return b_t;
	}
}
sf::Font& Resource_Manager::get_font(const int& id)
{
	auto font = font_library.find(id);
	if (font != font_library.end())
	{
		return font_library[id];
	}
	else
	{
		printf("RESOURCE MANAGER WARNING: font <%d> does not exist in library. An empty font is returned\n", id);
		return b_f;
	}
}

void Resource_Manager::clear_libraries()
{
	clear_fonts_library();
	clear_textures_library();
}