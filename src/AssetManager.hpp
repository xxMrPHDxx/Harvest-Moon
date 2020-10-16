#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include "pch.hpp"

// typedef std::map<std::string, sf::Texture*> TextureAtlas;
typedef std::map<std::string, void*> TableAtlas;

class AssetManager {
private:
	// TextureAtlas textures;
	TableAtlas tables;
public:
	AssetManager() {}
	virtual ~AssetManager(){
		// for(auto& pair : textures) delete pair.second;
		// for(auto& pair : tables)   delete pair.second;
	}

	static void register_class(lua_State*);

	static int create(lua_State*);
	static int destroy(lua_State*);

	static int get_table(lua_State*);
	static int set_table(lua_State*);

	static AssetManager* get_instance(lua_State* L);
};

#endif
