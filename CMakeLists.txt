cmake_minimum_required( VERSION 3.22 )

set( CMAKE_C_STANDARD 17 )
set( INCLUDE_FOLDER include )
set( SOURCE_FOLDER src )

set( HEADER_FILES ${INCLUDE_FOLDER}/board.h ${INCLUDE_FOLDER}/input.h )
set( SOURCE_FILES ${SOURCE_FOLDER}/main.c ${SOURCE_FOLDER}/board.c ${SOURCE_FOLDER}/input.c )

project( mineCper )

add_executable( mineCper ${SOURCE_FILES} ${HEADER_FILES} )
target_include_directories( mineCper PRIVATE ${INCLUDE_FOLDER} )

