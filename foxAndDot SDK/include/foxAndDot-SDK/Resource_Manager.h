#pragma once

//std  includes
#include <map>
#include <string>
#include <iostream>

//sfml includes
#include <SFML/Graphics.hpp>

//sdk  inludes
#include "Tools/Resource_Types.h"

class Scene_Component;

class  Resource_Manager
{

	friend class Core;

private:
	std::unordered_map<int, sf::Texture> texture_library;
	std::unordered_map<int, sf::Font>	    font_library;

public:

	Resource_Manager() = default;
	~Resource_Manager() = default;


	void add_texture(const std::string& texture_url, const int& id);//add texture in library
	void add_font(const std::string& font_url, const int& id);		//add font in library

	void drop_texture(const int& id);
	void drop_font(const int& id);
	void clear_textures_library();
	void clear_fonts_library();
	void clear_libraries(); //drop all fonts and textures

	sf::Texture& get_texture(const int& id); //get texture from library (You can control it)
	sf::Font& get_font(const int& id);		 //get font from library (You can control it)



private:
	void update_resource(Scene_Component*& component);
};
