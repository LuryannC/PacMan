//
// Created by luria on 16/10/2022.
//

#ifndef PACMANSFML_MAPHANDLER_H
#define PACMANSFML_MAPHANDLER_H
#include <SFML/Graphics.hpp>
#include "../GameObjects/TilesObject.h"

#include "vector"
#include "array"
#include "map"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class MapHandler
{
 public:
  explicit MapHandler(sf::RenderWindow& window);
  bool init();
  sf::IntRect makeTextureRect(int tile_ID, int sheet_size_x, int cell_size);
  void loadMap();
  sf::Vector2i vectorToId(sf::Vector2i vector);
  int toIndex(sf::Vector2i vector);
  static sf::Vector2i getDistance(sf::Vector2i start, sf::Vector2i end);
  sf::Vector2f toWorld(sf::Vector2i vector);

  tmx::Map map;
  static const int map_tiles = 30*34;
  std::array<std::array<std::unique_ptr<TilesObject>, map_tiles>, 3> tile;
  std::array<int, map_tiles> map_costs;
  int returnCost(int index);

 private:

  sf::Texture texture;
  sf::IntRect textureRect;
  sf::RenderWindow& window;
  static int const CELL_SIZE = 16;
  int MAP_WIDTH = 30;
  int MAP_HEIGHT = 34;
  int HALF_CELL = CELL_SIZE / 2;


  //std::vector<sf::Vector2f> walkable_paths;
};

#endif // PACMANSFML_MAPHANDLER_H
