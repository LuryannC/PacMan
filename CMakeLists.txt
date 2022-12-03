cmake_minimum_required(VERSION 3.14)
project(PacmanSFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH C:/)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

#------------------------------------------------------------------------------
# TMX getting imported inside this project
#------------------------------------------------------------------------------
message(STATUS  "TMXLITE:")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(VERBOSE "A lightweight C++14 parsing library for tmx map files created with the Tiled map editor. ")
message(STATUS "+ FETCHING TMXLITE TILED IMPORTER....")

if(BUILD_SHARED_LIBS)
    set (TMXLITE_STATIC_LIB "OFF" CACHE INTERNAL "OFF")
else()
    set (TMXLITE_STATIC_LIB "ON"  CACHE INTERNAL "ON")
endif()

include(FetchContent)
FetchContent_Declare(
        tmxlite
        GIT_REPOSITORY https://github.com/HuxyUK/tmxlite.git
        GIT_TAG        origin/master)

message(STATUS "+ CONFIGURING TMXLITE....")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

FetchContent_GetProperties(tmxlite)
if(NOT tmxlite_POPULATED)
    # Fetch the content using previously declared details
    FetchContent_Populate(tmxlite)

    # Set custom variables, policies, etc.
    # ...

    # Bring the populated content into the build
    add_subdirectory(${tmxlite_SOURCE_DIR}/tmxlite ${tmxlite_BINARY_DIR})
endif()

list(POP_BACK CMAKE_MESSAGE_INDENT)

set_target_properties(tmxlite PROPERTIES CXX_CLANG_TIDY "")
set_target_properties(tmxlite PROPERTIES CXX_CPPCHECK   "")
set_target_properties(tmxlite PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:tmxlite,INTERFACE_INCLUDE_DIRECTORIES>)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND ("x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
    target_compile_options(tmxlite PRIVATE /EHsc)
endif()

message(STATUS "+ DONE")
list(POP_BACK CMAKE_MESSAGE_INDENT)
#------------------------------------------------------------------------------
# END of the TMX settings
#------------------------------------------------------------------------------

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

INCLUDE_DIRECTORIES(  C:/vcpkg/packages/jsoncpp_x86-windows/include )
LINK_DIRECTORIES(  C:/vcpkg/packages/jsoncpp_x86-windows/lib )

file(GLOB LIBRARIES "C:/vcpkg/installed/x86-windows/lib/*.lib")
message("LIBRARIES = ${LIBRARIES}")

find_package(tmxlite)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)



set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/ResourceHandler.cpp src/ResourceHandler.h src/Scripts/Functions.cpp src/Scripts/Functions.h src/Entities/Entities.cpp src/Entities/Entities.h src/Scripts/GameStates.cpp src/Scripts/GameStates.h src/Scripts/GameStates/MainMenu.cpp src/Scripts/GameStates/MainMenu.h src/Scripts/GamesStatesEnum.h src/Scripts/GameStates/InGame.cpp src/Scripts/GameStates/InGame.h src/Scripts/GameStates/GameOver.cpp src/Scripts/GameStates/GameOver.h src/Scripts/MapHandler.cpp src/Scripts/MapHandler.h src/Entities/Player.cpp src/Entities/Player.h Data/GameObjects/Tiles.cpp Data/GameObjects/Tiles.h src/GameObjects/TilesObject.cpp src/GameObjects/TilesObject.h src/GameObjects/Coins.cpp src/GameObjects/Coins.h src/Scripts/Leaderboard.cpp src/Scripts/Leaderboard.h src/Scripts/Pathfinding.cpp src/Scripts/Pathfinding.h src/Entities/Enemy.cpp src/Entities/Enemy.h src/Scripts/BehaviourTree.cpp src/Scripts/BehaviourTree.h src/Scripts/Blackboard.cpp src/Scripts/Blackboard.h src/GameObjects/PowerPills.cpp src/GameObjects/PowerPills.h src/GameObjects/Cherry.cpp src/GameObjects/Cherry.h)
#set(tinyxml2 src/tinyxml2.cpp src/tinyxml2.h)
#set(TMXLoader TMXLoader/TMXLoader.cpp TMXLoader/TMXLoader.h TMXLoader/TMXMap.cpp TMXLoader/TMXMap.h TMXLoader/TMXMap.h TMXLoader/TMXTile.cpp TMXLoader/TMXTile.h TMXLoader/TMXTileLayer.cpp TMXLoader/TMXTileLayer.h TMXLoader/TMXTileSet.cpp TMXLoader/TMXTileSet.h TMXLoader/RapidXML/rapidxml.hpp TMXLoader/RapidXML/rapidxml_iterators.hpp TMXLoader/RapidXML/rapidxml_print.hpp TMXLoader/RapidXML/rapidxml_utils.hpp)


add_executable(PacmanSFML ${SOURCE_FILES})


target_link_libraries(PacmanSFML tmxlite)
target_link_libraries(PacmanSFML ${LIBRARIES})
target_link_libraries (PacmanSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)