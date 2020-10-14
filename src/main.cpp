#include <iostream>

#include "Game.hpp"
#include "SpriteSheet.hpp"

#define REGISTER(cls) cls::register_class(L)

int main(){
	// Create a new state
	lua_State* L = luaL_newstate();

	// Load all libraries
	luaL_openlibs(L);

	// Register all classes
	REGISTER(Game);
	// REGISTER(SpriteSheet);
	SpriteSheet::register_class(L);

	// Load a main script
	if(luaL_dofile(L, "Scripts/main.lua")){
		std::cout << "[Error]: " << lua_tostring(L, -1) << std::endl;
	}
}
