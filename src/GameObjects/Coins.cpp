//
// Created by luria on 06/11/2022.
//

#include "Coins.h"

Coins::Coins(float x, float y, sf::RenderWindow& window, int ID) :  Entities(x,y,window)
{
  id = ID;
  texture->loadFromFile("Data/Images/CoinPac.png");
  sprite->setPosition(x,y);
  sprite->setTexture(*texture);
}

bool Coins::isVisible() const
{
  return visible;
}
void Coins::setVisible(bool visible)
{
  Coins::visible = visible;
}
int Coins::getId() const
{
  return id;
}

