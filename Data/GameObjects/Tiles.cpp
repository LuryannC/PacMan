//
// Created by luria on 28/10/2022.
//

#include "Tiles.h"

Tiles::Tiles(int id, int cost) : ID(id), tile_cost(cost)
{
  ID = id;
  tile_cost = cost;
  sprite = std::make_unique<sf::Sprite>();
}

sf::Sprite& Tiles::getSprite()
{
  return *sprite;
}
int Tiles::getId() const
{
  return ID;
}
int Tiles::getTileCost() const
{
  return tile_cost;
}
void Tiles::setId(int id)
{
  ID = id;
}
void Tiles::setTileCost(int tileCost)
{
  tile_cost = tileCost;
}
