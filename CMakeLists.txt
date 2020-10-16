cmake_minimum_required( VERSION 3.10 )
project( harvest_moon )

if( DEFINED ENV{SFML_HOME_DIR} AND DEFINED ENV{LUA_HOME_DIR} )
	file( GLOB_RECURSE SRCS src/*.cpp EXCLUDE src/main.cpp )
	# set( SRCS
	# 	src/Game.cpp
	# 	src/SpriteSheet.cpp
	# 	src/Animation.cpp
	# 	src/main.cpp
	# )

	include_directories( PUBLIC $ENV{SFML_HOME_DIR}/include PUBLIC $ENV{LUA_HOME_DIR}/include )
	link_directories( $ENV{SFML_HOME_DIR}/lib $ENV{LUA_HOME_DIR}/lib ) 

	add_executable( hm ${SRCS} src/main.cpp )
	target_precompile_headers( hm PUBLIC src/pch.hpp )
	target_link_libraries( hm
		sfml-graphics
		sfml-window 
		sfml-system
		lua
	)
else ()
	message( FATAL_ERROR "Make sure to set 'SFML_HOME_DIR' and 'LUA_HOME_DIR' as environment variables!" )
endif ()
