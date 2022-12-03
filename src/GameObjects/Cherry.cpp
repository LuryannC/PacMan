//
// Created by luria on 28/11/2022.
//

#include "Cherry.h"
Cherry::Cherry(float x, float y, sf::RenderWindow& window) :  Entities(x,y,window)
{
  texture->loadFromFile("Data/Images/Cherry.png");
  sprite->setPosition(x,y);
  sprite->setTexture(*texture);
}

bool Cherry::isVisible() const
{
  return visible;
}
void Cherry::setVisible(bool visible)
{
  Cherry::visible = visible;
}
void Cherry::reset()
{
  setVisible(false);
  Entities::reset();
}
