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
	//--------------------------------------------------------------------------------------------------

		std::unordered_map<int, sf::Texture> texture_library; // Library of uploaded textures

		std::unordered_map<int, sf::Font>	    font_library; // Library of uploaded fonts

	//--------------------------------------------------------------------------------------------------
		
		static inline sf::Texture b_t;
	
		static inline sf::Font b_f;

	//--------------------------------------------------------------------------------------------------

		void update_resource(Scene_Component*& component);

	//--------------------------------------------------------------------------------------------------
public:

		Resource_Manager() = default;
		~Resource_Manager() = default;

	//INTERFACE
	//==================================================================================================
	
		void add_texture(const std::string& texture_url, const int& id);//add texture in library
		
		void add_font(const std::string& font_url, const int& id);		//add font in library

	//--------------------------------------------------------------------------------------------------

		void drop_texture(const int& id); // Drop texture from library
		
		void drop_font(const int& id);	  // Drop front from library
		
		void clear_textures_library();	  // Drop all textures
	
		void clear_fonts_library();		  // Drop all fonts
	
		void clear_libraries();			  // Drop all fonts and textures

	//--------------------------------------------------------------------------------------------------

		sf::Texture& get_texture(const int& id); // Get texture from library 
	
		sf::Font&    get_font(const int& id);	 // Get font from library 

	//==================================================================================================
};
