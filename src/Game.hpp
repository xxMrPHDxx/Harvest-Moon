#ifndef GAME_HPP
#define GAME_HPP

#include "pch.hpp"

class Game {
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock_global, clock_dt;
	float time, dt;
	sf::Vector2f scl;
public:
	Game() = delete; // Remove default constructor
	Game(int width, int height, std::string title) :
		scl(1.f, 1.f) {
		window = new sf::RenderWindow(
			sf::VideoMode(width, height),
			title,
			sf::Style::Close | sf::Style::Titlebar
		);
	}
	virtual ~Game(){ delete window; }

	static void register_class(lua_State*);

	static int create(lua_State*);
	static int destroy(lua_State*);

	static int get_time(lua_State*);
	static int get_dt(lua_State*);
	static int is_open(lua_State*);
	static int is_event_closed(lua_State*);
	static int set_scale(lua_State*);

	static int close(lua_State*);
	static int clear(lua_State*);
	static int draw(lua_State*);
	static int display(lua_State*);
	static int poll_event(lua_State*);
	static Game* get_instance(lua_State*);
};

#endif
