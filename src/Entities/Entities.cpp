//
// Created by luria on 14/10/2022.
//

#include "Entities.h"
Entities::Entities(float x, float y, sf::RenderWindow& window) : window(window)
{
  start_pos_x = x;
  start_pos_y = y;
  sprite = std::make_shared<sf::Sprite>();
  texture = std::make_shared<sf::Texture>();

}

bool Entities::initialiseSprite(sf::Texture& texture, const std::string& filename)
{
  if (!texture.loadFromFile(filename)){
    std::cout << "Failed to load: " + filename << std::endl;
    return false;
  }
  sprite->setTexture(texture);
  return true;
}

std::shared_ptr<sf::Sprite> Entities::getSprite()
{
  return sprite;
}
void Entities::keyPressed(sf::Event& event, float dt)
{

}
const sf::Vector2f& Entities::getVector2F() const
{
  return vector2F;
}
void Entities::setVector2F(const sf::Vector2f& vector2F)
{
  Entities::vector2F = vector2F;
}
float Entities::getVelocity() const
{
  return velocity;
}
float Entities::lerpFunction(float a, float b, float f)
{
  return a * (1.0 - f) + (b * f);
}
void Entities::setDestination(std::vector<sf::Vector2f> path)
{
  destination = path;

  setRotation();
}
void Entities::setRotation()
{
  if (!destination.empty())
  {
    if (destination[0].x == sprite->getPosition().x && destination[0].y == sprite->getPosition().y)
      return ;

    direction.x = destination[0].x - sprite->getPosition().x;
    direction.y = destination[0].y - sprite->getPosition().y;
    float normalise = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= normalise;
    direction.y /= normalise;
  }
}
void Entities::update(float dt)
{

}
void Entities::render(){
}
void Entities::reset() {}
int Entities::getSpeed() const
{
  return speed;
}
void Entities::setSpeed(int speed)
{
  Entities::speed = speed;
}
const std::vector<sf::Vector2f>& Entities::getDestination() const
{
  return destination;
}
