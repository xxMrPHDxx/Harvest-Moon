#include "AssetManager.hpp"

#define AM AssetManager

void AM::register_class(lua_State* L){
	// Create an empty table
	lua_newtable(L);
	// Set the __index
	lua_pushstring(L, "AssetManager");
	lua_setfield(L, -2, "__index");
	// Set the AssetManager::new(...)
	lua_pushcfunction(L, create);
	lua_setfield(L, -2, "new");
	// Set as global
	lua_setglobal(L, "AssetManager");
}

int AM::create(lua_State* L){
	// Create an empty table
	lua_newtable(L);
	// Set the instance methods
	luaL_Reg methods[] = {
		{ "destroy", destroy },
		{ "get_table", get_table },
		{ "set_table", set_table }
	};
	for(luaL_Reg& reg : methods){
		lua_pushcfunction(L, reg.func);
		lua_setfield(L, -2, reg.name);
	}
	// Create and set the instance pointer
	lua_pushlightuserdata(L, new AM());
	lua_setfield(L, -2, "ptr");
	// Set the metatable
	lua_getglobal(L, "AssetManager");
	lua_setmetatable(L, -2);
	return 1;
}

int AM::destroy(lua_State* L){
	delete get_instance(L);
	lua_pop(L, 1);
	lua_pushnil(L);
	return 1;
}

int AM::get_table(lua_State* L){
	// Check the arguments (key: string)
	if(lua_gettop(L) != 2 || !lua_isstring(L, -1))
		throw luaL_error(L, "AssetManager:get_table(...) expects a string!");
	// Get and pop the argument
	std::string key = static_cast<std::string>(lua_tostring(L, -1));
	lua_pop(L, 1);
	// Get the instance
	AM& am = *get_instance(L);
	// Check if the key exists and throw error if not
	if(!am.tables.count(key))
		throw luaL_error(L, "Cannot find table with the given key!");
	// Return the spritetable
	lua_pushlightuserdata(L, am.tables[key]);
	return 1;
}

int AM::set_table(lua_State* L){
	// Check the arguments (key: string, sprite: table)
	if(lua_gettop(L) != 3 || !lua_isstring(L, -2) || !lua_istable(L, -1))
		throw luaL_error(L, "AssetManager:get_table(...) expects string and a table!");
	// Get the arguments and pop them
	std::string key = static_cast<std::string>(lua_tostring(L, -2));
	void* val = const_cast<void*>(lua_topointer(L, -2));
	lua_pop(L, 2);
	// Get the instance
	AM& am = *get_instance(L);
	// Set the key and value
	std::cout << "Key: " << key << ", table: " << val << std::endl;
	am.tables.insert({ key, val });
	return 1;
}

AM* AM::get_instance(lua_State* L){
	lua_getfield(L, -1, "ptr");
	AM* am = (AM*) lua_touserdata(L, -1);
	lua_pop(L, 1);
	return am;
}
