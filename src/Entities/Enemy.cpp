//
// Created by luria on 10/11/2022.
//

#include "Enemy.h"
Enemy::Enemy(float x, float y, sf::RenderWindow& window, int start_rect) :
  Entities(x, y, window)
{
  start_pos_x = x;
  start_pos_y = y;
  rect_pos = start_rect;
}
bool Enemy::init()
{
  state = static_cast<int>(AnimationState::HUNT);

  Functions::generate(*sprite,
                      *texture,
                      "Data/Images/ghosts.png",
                      start_pos_x,
                      start_pos_y,
                      1,
                      1);

  frame = sf::IntRect(0, rect_pos, 16, 16);
  sprite->setTextureRect(sf::IntRect(frame));

  return false;
}
void Enemy::update(float dt)
{
  if (!destination.empty())
  {
    float pos = abs((sprite->getPosition().x - destination[0].x) - (sprite->getPosition().y - destination[0].y));
    if (pos < speed * 0.02f)
    {
      sprite->setPosition(destination[0].x, destination[0].y);
      destination.erase(destination.begin());
      setRotation();
    }
    sprite->move(direction.x * speed * dt, direction.y * speed * dt);
  }
  AnimationHandler();

  Entities::update(dt);
}

bool Enemy::checkCollision(sf::Sprite entity)
{
  if (entity.getGlobalBounds().intersects(sprite->getGlobalBounds()))
  {
    return true;
  }
  return false;
}
void Enemy::reset()
{
  sprite->setPosition(start_pos_x, start_pos_y);
  state = static_cast<int>(AnimationState::HUNT);
  destination = {};
  direction = {};
  Entities::reset();
}
void Enemy::AnimationHandler()
{
  if (animation_clock.getElapsedTime().asSeconds() >= update_rate)
  {
    if (state == static_cast<int>(AnimationState::HUNT)) /// MOVING DOWN
    {
      frame.left += 16;
      frame.width = 16;
      frame.top   = rect_pos;
      if (frame.left >= 16)
      {
        frame.left = 0;
      }

    }
    else if (state == static_cast<int>(AnimationState::FLEE)) /// MOVING DOWN
    {
      frame.left += 16;
      frame.width = 16;
      frame.top = 0.f;
      if (frame.left >= 32)
      {
        frame.left = 0;
      }
    }
    animation_clock.restart();
    sprite->setTextureRect(frame);
  }
}
int Enemy::getState() const
{
  return state;
}
void Enemy::setState(int state)
{
  Enemy::state = state;
}
