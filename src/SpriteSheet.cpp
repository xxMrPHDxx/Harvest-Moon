#include "SpriteSheet.hpp"

void SpriteSheet::register_class(lua_State* L){
	// Create an empty table
	lua_newtable(L);
	// Add the __index
	lua_pushstring(L, "SpriteSheet");
	lua_setfield(L, -2, "__index");
	// Set the SpriteSheet:new(string) method
	lua_pushcfunction(L, create);
	lua_setfield(L, -2, "new");
	// Set as global
	lua_setglobal(L, "SpriteSheet");
}

int SpriteSheet::create(lua_State* L){
	// Check for arguments
	if(lua_gettop(L) != 2){
		throw luaL_error(L, "SpriteSheet:new(...) expects string as argument!");
	}
	// Get the path
	std::string path = static_cast<std::string>(lua_tostring(L, -1));
	lua_pop(L, 1);
	// Create empty table instance
	lua_newtable(L);
	// Set the instance methods
	luaL_Reg methods[] = {
		{ "destroy", destroy },
		{ "get", get },
		{ "define", define }
	};
	for(luaL_Reg& reg : methods){
		lua_pushcfunction(L, reg.func);
		lua_setfield(L, -2, reg.name);
	}
	// Set the instance to ptr
	try{
		lua_pushlightuserdata(L, new SpriteSheet(path));
		lua_setfield(L, -2, "ptr");
	}catch(std::invalid_argument& e){
		throw luaL_error(L, e.what());
	}
	// Set the metatable
	lua_getglobal(L, "SpriteSheet");
	lua_setmetatable(L, -2);
	return 1;
}

int SpriteSheet::destroy(lua_State* L){
	delete get_instance(L);
	lua_pop(L, 1);
	lua_pushnil(L);
	return 1;
}

int SpriteSheet::get(lua_State* L){
	// Check for arguments (string)
	if(lua_gettop(L) != 2 || !lua_isstring(L, -1))
		throw luaL_error(L, "SpriteSheet:get(...) expects a (string)");
	// Get and pop the argument
	std::string key = static_cast<std::string>(lua_tostring(L, -1));
	lua_pop(L, 1);
	// Get the instance
	SpriteSheet& ss = *get_instance(L);
	// Check whether the sprite key exists or not
	if(!ss.sprites.count(key)){
		std::cout << "Cannot find sprite with key '" << key << "'!\n";
		throw luaL_error(L, "");
	}
	lua_pushlightuserdata(L, ss.sprites.find(key)->second);
	return 1;
}

int SpriteSheet::define(lua_State* L){
	// Check for arguments (key, x, y, w, h)
	if(lua_gettop(L) != 6 || 
			!lua_isstring(L, -5) ||
			!lua_isinteger(L, -4) ||
			!lua_isinteger(L, -3) ||
			!lua_isinteger(L, -2) ||
			!lua_isinteger(L, -1))
		throw luaL_error(L, "SpriteSheet:define(...) expects (string, int, int, int, int)!");
	// Get the arguments and pop them all
	std::string key = static_cast<std::string>(lua_tostring(L, -5));
	int x = static_cast<int>(lua_tointeger(L, -4));
	int y = static_cast<int>(lua_tointeger(L, -3));
	int w = static_cast<int>(lua_tointeger(L, -2));
	int h = static_cast<int>(lua_tointeger(L, -1));
	lua_pop(L, 5);
	// Get the instance
	SpriteSheet& ss = *get_instance(L);
	// Create the sf::Sprite
	sf::Sprite* spr = new sf::Sprite();
	spr->setTexture(ss.tex);
	spr->setTextureRect(sf::IntRect(x, y, w, h));
	// Set the key and sf::Sprite
	ss.sprites.insert({ key, spr });
	return 1;
}

SpriteSheet* SpriteSheet::get_instance(lua_State* L){
	lua_getfield(L, -1, "ptr");
	SpriteSheet* ss = (SpriteSheet*) lua_touserdata(L, -1);
	lua_pop(L, 1);
	return ss;
}
