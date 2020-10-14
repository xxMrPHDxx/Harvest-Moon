#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include "pch.hpp"

class SpriteSheet {
private:
	sf::Texture tex;
	std::map<std::string,sf::Sprite*> sprites;
public:
	SpriteSheet(std::string path){
		if(!tex.loadFromFile(path))
			throw std::invalid_argument("Error: Failed to load texture!");
	}
	virtual ~SpriteSheet(){
		for(auto& pair : sprites)
			delete pair.second;
	}

	static void register_class(lua_State*);

	static int create(lua_State*);
	static int destroy(lua_State*);

	static int get(lua_State*);

	static int define(lua_State*);
	static SpriteSheet* get_instance(lua_State*);
};

#endif
