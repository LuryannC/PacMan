//
// Created by luria on 28/10/2022.
//

#ifndef PACMANSFML_TILES_H
#define PACMANSFML_TILES_H
#include <SFML/Graphics.hpp>

class Tiles
{
 public:
  Tiles(int id, int cost);
  sf::Sprite& getSprite();
  int getId() const;
  int getTileCost() const;
  void setId(int id);
  void setTileCost(int tileCost);

 private:
  int ID;
  int tile_cost;

 private:
  std::unique_ptr<sf::Sprite> sprite = nullptr;

};

#endif // PACMANSFML_TILES_H
