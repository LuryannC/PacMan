//
// Created by luria on 03/11/2022.
//

#include "TilesObject.h"
TilesObject::TilesObject(float x, float y, sf::RenderWindow& window, int ID) :  Entities(x,y,window)
{
  id = ID;
}
int TilesObject::getId() const
{
  return id;
}
bool TilesObject::isVisible() const
{
  return visible;
}
void TilesObject::setVisible(bool visible)
{
  TilesObject::visible = visible;
}
void TilesObject::setId(int id)
{
  TilesObject::id = id;
}
int TilesObject::getCost() const
{
  return cost;
}
void TilesObject::setCost(int cost)
{
  TilesObject::cost = cost;
}
int TilesObject::tileAsId(sf::Vector2i vector)
{
  return int((int((vector.y + HALF_CELL - int((window.getSize().y - (CELL_SIZE * MAP_HEIGHT)) / 2)) / CELL_SIZE) * MAP_WIDTH) + int((vector.x + HALF_CELL - int((window.getSize().x - (CELL_SIZE * MAP_WIDTH)) / 2)) / CELL_SIZE));
}