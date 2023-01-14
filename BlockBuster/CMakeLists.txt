cmake_minimum_required(VERSION 3.16)

add_executable(BlockBuster
	include/BlockBuster/Common.h
	include/BlockBuster/Crate.h
	include/BlockBuster/Bob.h
	include/BlockBuster/Map.h
	include/BlockBuster/Application.h
	include/BlockBuster/ResourceManager.h
	include/BlockBuster/StaticBlock.h
	include/BlockBuster/CrateSpot.h
	include/BlockBuster/LevelEditor.h
	include/BlockBuster/Block.h
	include/BlockBuster/Grid.h

	src/BlockBuster/Grid.cpp
	src/BlockBuster/Block.cpp
	src/BlockBuster/LevelEditor.cpp
	src/BlockBuster/CrateSpot.cpp
	src/BlockBuster/StaticBlock.cpp
	src/BlockBuster/main.cpp
	src/BlockBuster/Crate.cpp
	src/BlockBuster/Map.cpp
	src/BlockBuster/Bob.cpp
	src/BlockBuster/Application.cpp
	src/BlockBuster/ResourceManager.cpp
)

target_link_libraries(BlockBuster
	PUBLIC
	opengl32
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
	Utils
	tinyxml2
)

target_include_directories(BlockBuster
	PRIVATE
	./include/
	../Utils/include/
)

add_compile_definitions(
	RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)