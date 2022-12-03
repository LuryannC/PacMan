//
// Created by luria on 14/10/2022.
//

#ifndef PACMANSFML_ENTITIES_H
#define PACMANSFML_ENTITIES_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Scripts/Functions.h"
#include <iostream>
#include <cassert>
#include <cmath>

enum class AnimationState
{
  IDLE,
  MOVING,
  DEAD,
  MOVING_UP,
  MOVING_DOWN,
  HUNT,
  FLEE,
};

class Entities
{
 public:
  explicit Entities(float x, float y, sf::RenderWindow& window);
  bool initialiseSprite(sf::Texture &texture, const std::string& filename);
  std::shared_ptr<sf::Sprite> getSprite();
  virtual void keyPressed(sf::Event& event, float dt);
  const sf::Vector2f& getVector2F() const;
  void setVector2F(const sf::Vector2f& vector2F);
  float getVelocity() const;
  float lerpFunction(float a, float b, float f);
  virtual void update(float dt);
  void render();
  virtual void reset();

  void setDestination(std::vector<sf::Vector2f> path);
  void setRotation();

  int getSpeed() const;
  void setSpeed(int speed);
  const std::vector<sf::Vector2f>& getDestination() const;

 private:

  // position

 protected:
  std::shared_ptr<sf::Sprite> sprite;
  std::shared_ptr<sf::Texture> texture;
  sf::RenderWindow& window;
  std::vector<sf::Vector2f> destination;
  sf::Vector2f direction;
  sf::Vector2i position;
  // Movement
  float velocity;
  int speed = 45;
  float start_pos_x;
  float start_pos_y;

 protected:
  sf::Vector2f vector2F;

};

#endif // PACMANSFML_ENTITIES_H
