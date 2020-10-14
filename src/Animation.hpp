#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "pch.hpp"

class SpriteSheet;

class Animation {
private:
	SpriteSheet& sheet;
	std::vector<std::string> frames;
	sf::Clock timer;
	float speed;
	int idx = 0;
public:
	Animation(SpriteSheet& sheet, float speed) : 
		sheet(sheet),
		speed(speed) { }
	virtual ~Animation() {}

	static void register_class(lua_State*);

	static int create(lua_State*);
	static int destroy(lua_State*);

	static int get(lua_State*);

	static int add(lua_State*);
	static int update(lua_State*);
	static Animation* get_instance(lua_State*);
};

#endif
