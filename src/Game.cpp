#include "Game.hpp"

void Game::register_class(lua_State* L){
	// Create an empty table
	lua_newtable(L);
	// Set __index to "Game"
	lua_pushstring(L, "Game");
	lua_setfield(L, -2, "__index");
	// Set the Game:new(...) contructor
	lua_pushcfunction(L, create);
	lua_setfield(L, -2, "new");
	// Set as global
	lua_setglobal(L, "Game");
}

int Game::create(lua_State* L){
	// Check for arguments (width, height, title), else set to defaults
	int width = 640, height = 480; std::string title = "Untitled Game";
	if(lua_gettop(L) == 4 && lua_isinteger(L, -3) && lua_isinteger(L, -2) && lua_isstring(L, -1)){
		width  = static_cast<int>(lua_tointeger(L, -3));
		height = static_cast<int>(lua_tointeger(L, -2));
		title  = static_cast<std::string>(lua_tostring(L, -1));
		lua_pop(L, 3);
	}

	// Create an empty table for our instance
	lua_newtable(L);
	
	// Set all the instance methods
	luaL_Reg methods[] = {
		{ "destroy", destroy },
		{ "is_open", is_open },
		{ "is_event_closed", is_event_closed },
		{ "poll_event", poll_event },
		{ "close", close },
		{ "draw", draw },
		{ "display", display }
	};
	for(luaL_Reg& reg : methods){
		lua_pushcfunction(L, reg.func);
		lua_setfield(L, -2, reg.name);
	}

	// Set the ptr to a new Game
	lua_pushlightuserdata(L, new Game(width, height, title));
	lua_setfield(L, -2, "ptr");

	// Set the metatable
	lua_getglobal(L, "Game");
	lua_setmetatable(L, -2);
	return 1;
}

int Game::destroy(lua_State* L){
	delete get_instance(L);
	lua_pop(L, 1);
	lua_pushnil(L);
	return 1;
}

int Game::is_open(lua_State* L){
	Game& g = *get_instance(L);
	lua_pushboolean(L, g.window->isOpen());
	return 1;
}

int Game::is_event_closed(lua_State* L){
	Game& g = *get_instance(L);
	lua_pushboolean(L, g.event.type == sf::Event::Closed);
	return 1;
}

int Game::poll_event(lua_State* L){
	Game& g = *get_instance(L);
	lua_pushboolean(L, g.window->pollEvent(g.event));
	return 1;
}

int Game::close(lua_State* L){
	Game& g = *get_instance(L);
	g.window->close();
	return 1;
}

int Game::draw(lua_State* L){
	// Check for sprite userdata
	if(lua_gettop(L) == 2 && lua_isuserdata(L, -1)){
		return 1;
	}
	// Get the sprite ptr and pop the stack
	sf::Sprite* spr = (sf::Sprite*) lua_touserdata(L, -1);
	lua_pop(L, 1);
	// Get the game instance
	Game& g = *get_instance(L);
	// Draw the sprite
	g.window->draw(*spr);
	return 1;
}

int Game::display(lua_State* L){
	Game& g = *get_instance(L);
	g.window->display();
	return 1;
}

Game* Game::get_instance(lua_State* L){
	lua_getfield(L, -1, "ptr");
	Game* g = (Game*) lua_touserdata(L, -1);
	lua_pop(L, 1);
	return g;
}
