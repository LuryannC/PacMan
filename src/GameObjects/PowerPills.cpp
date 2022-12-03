//
// Created by luria on 21/11/2022.
//

#include "PowerPills.h"
PowerPills::PowerPills(float x, float y, sf::RenderWindow& window, int ID) :  Entities(x,y,window)
{
  texture->loadFromFile("Data/Images/PowerPill.png");
  sprite->setPosition(x,y);
  sprite->setTexture(*texture);
  id = ID;
}
bool PowerPills::checkCollision(sf::Sprite entity)
{
  if (entity.getGlobalBounds().intersects(sprite->getGlobalBounds()))
  {
    return true;
  }
  return false;
}
bool PowerPills::isVisible() const
{
  return visible;
}
void PowerPills::setVisible(bool visible)
{
  PowerPills::visible = visible;
}
int PowerPills::getId() const
{
  return id;
}
void PowerPills::reset()
{
  setVisible(true);
  Entities::reset();
}
