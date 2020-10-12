cmake_minimum_required( VERSION 3.10 )
project( harvest_moon )

set( SFML_HOME_DIR ../SFML-2.5.1 )
set( LUA_HOME_DIR ../lua-5.4.1 )

file( GLOB_RECURSE SRCS src/*.cpp )

include_directories( PUBLIC ${SFML_HOME_DIR}/include PUBLIC ${LUA_HOME_DIR}/include )
link_directories( ${SFML_HOME_DIR}/lib ${LUA_HOME_DIR}/lib ) 

add_executable( hm ${SRCS} )
target_precompile_headers( hm PUBLIC src/pch.hpp )
target_link_libraries( hm sfml-graphics sfml-window sfml-system lua )
