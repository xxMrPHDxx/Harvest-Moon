#include "Animation.hpp"
#include "SpriteSheet.hpp"

void Animation::register_class(lua_State* L){
	// Create an empty table
	lua_newtable(L);
	// Set the __index
	lua_pushstring(L, "Animation");
	lua_setfield(L, -2, "__index");
	// Set the Animation:new method
	lua_pushcfunction(L, create);
	lua_setfield(L, -2, "new");
	// Set as global
	lua_setglobal(L, "Animation");
}

int Animation::create(lua_State* L){
	// Check for arguments (spritesheet: table, speed: number)
	if(lua_gettop(L) != 3 || !lua_istable(L, -2) || !lua_isnumber(L, -1))
		throw luaL_error(L, "Animation:new(...) expects a SpriteSheet (table) and a speed (float)");
	// Get the speed and pop it
	float speed = static_cast<float>(lua_tonumber(L, -1));
	lua_pop(L, 1);
	// Get the spritesheet and pop it
	SpriteSheet& ss = *SpriteSheet::get_instance(L);
	lua_pop(L, 1);
	// Create an empty table
	lua_newtable(L);
	// Set the instance methods
	luaL_Reg methods[] = {
		{ "destroy", destroy },
		{ "get", get },
		{ "add", add },
		{ "update", update }
	};
	for(luaL_Reg& reg : methods){
		lua_pushcfunction(L, reg.func);
		lua_setfield(L, -2, reg.name);
	}
	// Set the instance pointer
	lua_pushlightuserdata(L, new Animation(ss, speed));
	lua_setfield(L, -2, "ptr");
	// Set the metatable
	lua_getglobal(L, "Animation");
	lua_setmetatable(L, -2);
	return 1;
}

int Animation::destroy(lua_State* L){
	delete get_instance(L);
	lua_pop(L, 1);
	lua_pushnil(L);
	return 1;
}

int Animation::get(lua_State* L){
	// Get the Animation instance
	Animation& a = *get_instance(L);
	// Check if there's any frames
	if(!a.frames.size())
		throw luaL_error(L, "There's no frame in the animation");
	// Push in the sprite to draw
	std::string& frame_name = a.frames[a.idx];
	lua_pushlightuserdata(L, &a.sheet[frame_name]);
	return 1;
}

int Animation::add(lua_State* L){
	// Check the arguments for frame name
	if(lua_gettop(L) != 2 || !lua_isstring(L, -1))
		throw luaL_error(L, "Animation:add(...) expects a string");
	// Get the argument and pop it
	std::string frame_name = static_cast<std::string>(lua_tostring(L, -1));
	lua_pop(L, 1);
	// Get the animation instance
	Animation& a = *get_instance(L);
	// Add to the frames
	a.frames.push_back(frame_name);
	return 1;
}

int Animation::update(lua_State* L){
	// Get the Animation instance
	Animation& a = *get_instance(L);
	/* Check if the index should be incremented.
	 * Increment it if it passes the frame speed
	 * and restart the clock.
	 */
	if(a.timer.getElapsedTime().asMilliseconds() >= a.speed){
		a.idx = (a.idx + 1) % a.frames.size();
		a.timer.restart();
	}
	return 1;
}

Animation* Animation::get_instance(lua_State* L){
	lua_getfield(L, -1, "ptr");
	Animation* a = (Animation*) lua_touserdata(L, -1);
	lua_pop(L, 1);
	return a;
}
