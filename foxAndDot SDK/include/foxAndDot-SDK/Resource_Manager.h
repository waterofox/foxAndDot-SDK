#pragma once

//std includes
#include <map>
#include <string>
#include <iostream>

//sfml includes
#include <SFML/Graphics.hpp>

class Scene_Component;

//RESOURCE MANAGER
class  Resource_Manager
{

	friend class Core;

	//TYPES OF RESOURCES
public:
	enum  resource_type
	{
		texture = 0,
		font = 1,
		no_resource = 2
	};

	//FIELDS
private:
	std::map<int, sf::Texture> texture_library;
	std::map<int, sf::Font>	      font_library;

	//METHODS
public:

	Resource_Manager() = default;
	~Resource_Manager() = default;

	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	void add_texture(const std::string& texture_url, const int& id);//add texture in library
	void add_font(const std::string& font_url, const int& id);		//add font in library

	void clear_libraries(); //drop all fonts and textures

	sf::Texture& get_texture(const int& id); //get texture from library (You can control it)
	sf::Font& get_font(const int& id);		 //get font from library (You can control it)
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


private:
	void update_resource(Scene_Component*& component);
};
