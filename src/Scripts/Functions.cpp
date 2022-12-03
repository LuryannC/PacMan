//
// Created by luria on 14/10/2022.
//

#include "Functions.h"
#include <iostream>
void Functions::generate(sf::Text& variable_name, const std::string& string, sf::Font& font, const sf::Color& colour, float pos_x,
                         float pos_y, int character_size)
{
  variable_name.setString(string);
  variable_name.setFont(font);
  variable_name.setFillColor(colour);
  variable_name.setPosition(pos_x, pos_y);
  variable_name.setCharacterSize(character_size);
}

void Functions::generate(
  sf::Sprite& sprite, sf::Texture& texture, const std::string& filename, float pos_x,
  float pos_y, float scale_x, float scale_y)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  sprite.setTexture(texture);
  sprite.setPosition(pos_x, pos_y);
  sprite.setScale(scale_x, scale_y);
}

/// Collisions

bool Functions::collisionCheck(sf::Sprite& object_1, sf::Sprite& object_2, float player_offset, float item_offset)
{
  float object_1_tl_x = object_1.getPosition().x + player_offset;
  float object_1_tl_y = object_1.getPosition().y;
  float object_1_br_x = object_1.getPosition().x + object_1.getGlobalBounds().width - player_offset;
  float object_1_br_y = object_1.getPosition().y + object_1.getGlobalBounds().height;


  float object_2_tl_x = object_2.getPosition().x + item_offset;
  float object_2_tl_y = object_2.getPosition().y;
  float object_2_br_x = object_2.getPosition().x + object_2.getGlobalBounds().width - item_offset;
  float object_2_br_y = object_2.getPosition().y + object_2.getGlobalBounds().height;


  if (object_1_br_x > object_2_tl_x &&
      object_1_tl_x < object_2_br_x &&
      object_1_br_y > object_2_tl_y &&
      object_1_tl_y < object_2_br_y)
  {
    return true;
  }
  return false;
}
bool Functions::collisionCheck(sf::Sprite& object_1, sf::RectangleShape& object_2, float player_offset, float item_offset)
{
  float object_1_tl_x = object_1.getPosition().x + player_offset;
  float object_1_tl_y = object_1.getPosition().y;
  float object_1_br_x = object_1.getPosition().x + object_1.getGlobalBounds().width - player_offset;
  float object_1_br_y = object_1.getPosition().y + 20.f;


  float object_2_tl_x = object_2.getPosition().x + item_offset;
  float object_2_tl_y = object_2.getPosition().y;
  float object_2_br_x = object_2.getPosition().x + object_2.getGlobalBounds().width - item_offset;
  float object_2_br_y = object_2.getPosition().y + object_2.getGlobalBounds().height;


  if (object_1_br_x > object_2_tl_x &&
      object_1_tl_x < object_2_br_x &&
      object_1_br_y > object_2_tl_y &&
      object_1_tl_y < object_2_br_y)
  {
    return true;
  }
  return false;
}

bool Functions::collisionXBox(sf::Sprite& object_1, sf::RectangleShape& object_2)
{
  float object_1_mid_point = object_1.getPosition().x + object_1.getGlobalBounds().width / 2;

  float object_2_left = object_2.getPosition().x + 0.2f;
  float object_2_right = object_2.getPosition().x + object_2.getGlobalBounds().width - 0.2f;

  if (object_1_mid_point < object_2_right &&
      object_1_mid_point > object_2_left)
  {
    return true;
  }
  return false;
}

bool Functions::platformCollision(sf::Sprite& object_1, sf::RectangleShape& object_2, float offset)
{
  /// Sprite
  float object_1_tl_x = object_1.getPosition().x + offset;
  float object_1_tl_y = object_1.getPosition().y + object_1.getGlobalBounds().height - 13.f;
  float object_1_br_x = object_1.getPosition().x + object_1.getGlobalBounds().width - offset;
  float object_1_br_y = object_1.getPosition().y + object_1.getGlobalBounds().height;

  /// Rectangle
  float object_2_tl_x = object_2.getPosition().x;
  float object_2_tl_y = object_2.getPosition().y + 5.f;
  float object_2_br_x = object_2.getPosition().x + object_2.getGlobalBounds().width;
  float object_2_br_y = object_2.getPosition().y + 13.f;


  if (object_1_br_x > object_2_tl_x &&
      object_1_tl_x < object_2_br_x &&
      object_1_br_y > object_2_tl_y &&
      object_1_tl_y < object_2_br_y)
  {
    return true;
  }
  return false;
}

bool Functions::floorCheck(sf::Sprite* object_1, sf::Sprite* object_2)
{
  float object_1_b = object_1->getPosition().y + object_1->getGlobalBounds().height;

  float object_2_t = object_2->getPosition().y;

  if (object_1_b < object_2_t)
  {
    object_1->setPosition(object_1->getPosition().x, object_2->getPosition().y - object_1->getGlobalBounds().height);
    return true;
  }
  return false;
}

bool Functions::wallsCollision(sf::Sprite& object, sf::RenderWindow& window)
{
  if (object.getPosition().x <= 0 ||
      object.getPosition().x + object.getGlobalBounds().width >= window.getSize().x ||
      object.getPosition().y <= 0 ||
      object.getPosition().y + object.getGlobalBounds().height >= window.getSize().y)
  {
    return true;
  }
  return false;
}
bool Functions::wallsCollision(sf::Sprite& object, float max_window_size, float player_offset)
{
  if (object.getPosition().x  + player_offset <= 0 ||
      object.getPosition().x + object.getGlobalBounds().width - player_offset + 4.0f>= max_window_size)
  {
    return true;
  }
  return false;
}

bool Functions::windowBottom(sf::Sprite& player, float window_y, float offset)
{
  if (player.getPosition().y + offset >= window_y)
  {
    return true;
  }
  return false;
}


void Functions::updateAnimation(sf::Sprite& sprite, sf::Clock& timer, float update_rate, int state, sf::IntRect& current_frame, int max, int size)
{
  ////////////////////////////////////////////////////////////
  ///
  /// @brief A function that creates the animation loop
  /// It takes 7 parameters:
  ///
  /// @param sprite: Reference to the sprite
  ///
  /// @param timer: timer to set the animation loop time
  ///
  /// @param update_rate: the update rate that the animation will play
  ///
  /// @param state: tell which animation should be played **
  ///
  /// @param current_frame: the frame that will be updated
  ///
  /// @param top_max: maximum value of the animation sheet -
  /// current size of the size of the sprite pixels
  ///
  /// @param size: pixel size of the sprite
  ///
  /// @param ** state order (int) : IDLE = 0, MOVING, JUMP...
  ////////////////////////////////////////////////////////////


  if (timer.getElapsedTime().asSeconds() >= update_rate)
  {
    if (state == 0) /// If IDLE
    {
      current_frame.left = 0;
      current_frame.width = size;
      current_frame.top = 0;
      if (current_frame.left >= size)
      {
        current_frame.left = 0;
      }
    }
    else if (state == 1) /// Moving
    {
      current_frame.left += size;
      current_frame.width = size;
      current_frame.top = 16.f;
      if (current_frame.left >= max)
      {
        current_frame.left = 0;
      }
    }
    else if (state == 2) /// Dead
    {
      current_frame.left += size;
      current_frame.width = size;
      current_frame.top = 32.f;
      if (current_frame.left >= max)
      {
        current_frame.left = 0;
      }
    }
    else if (state == 3) /// MOVING UP
    {
      current_frame.left += size;
      current_frame.width = size;
      current_frame.top = 48.f;
      if (current_frame.left >= max)
      {
        current_frame.left = 0;
      }
    }
    else if (state == 4) /// MOVING DOWN
    {
      current_frame.left += size;
      current_frame.width = size;
      current_frame.top = 64.f;
      if (current_frame.left >= max)
      {
        current_frame.left = 0;
      }
    }
    else if (state == 6) /// HUNT
    {
      current_frame.left += size;
      current_frame.width = size;
      current_frame.top = 0.f;
      if (current_frame.left >= max)
      {
        current_frame.left = 0;
      }
    }
    timer.restart();
    sprite.setTextureRect(current_frame);
  }
}
float Functions::resetVectorY(sf::Vector2f& velocity)
{
  return velocity.y = 0.0;
}
/// Creates a following camera with clamping X "1560" hardcoded value
void Functions::cameraSystem(sf::View &camera, sf::Window& window, float dt, const sf::Sprite& player)
{
  if (player.getPosition().x + player.getGlobalBounds().width / 2 > window.getSize().x / 2)
  {
    camera.setCenter(sf::Vector2f(player.getPosition().x + player.getGlobalBounds().width / 2, window.getSize().y / 2));
  }
  if (player.getPosition().x + player.getGlobalBounds().width / 2 > 1560)
  {
    camera.setCenter(sf::Vector2f(1560, window.getSize().y / 2));
  }
}

int Functions::randomize(int min, int max)
{
  int value = min + rand() / (RAND_MAX /(max - min));
  return value;
}

void Functions::moveEnemy(sf::Sprite& enemy, sf::RectangleShape& platform, float dt, float offset, sf::Vector2f& direction, float speed)
{
  /// Platform
  float platform_max_left = platform.getPosition().x;
  float platform_max_right = platform_max_left + platform.getGlobalBounds().width;

  /// Enemy
  float enemy_left = enemy.getPosition().x + offset;
  float enemy_right = enemy_left + enemy.getGlobalBounds().width - offset;

  if (enemy_left - 2.0f < platform_max_left)
  {
    direction.x = -direction.x;
    enemy.setScale(2.4, 2.4);
    enemy.setOrigin(0, 0);
  }
  else if (enemy_right + 2.0f > platform_max_right)
  {
    direction.x = -direction.x;
    enemy.setScale(-2.4, 2.4);
    enemy.setOrigin(enemy.getGlobalBounds().width / 2.4, 0);
  }
  enemy.move(speed * dt * direction.x, 0);
}

bool Functions::enemyCollision(
  sf::Sprite& player, sf::Sprite& enemy, float player_offset, float enemy_offset)
{
  /// Player
  float player_x = player.getPosition().x + (player_offset * 2.4);
  float player_w = player_x + player.getGlobalBounds().width - (player_offset * 2.4);
  float player_y = player.getPosition().y;
  float player_h = player_y + player.getGlobalBounds().height;

  /// Enemy

  float enemy_x = enemy.getPosition().x + enemy_offset;
  float enemy_w = enemy_x + enemy.getGlobalBounds().width - enemy_offset;
  float enemy_y = enemy.getPosition().y - 5.f;
  float enemy_h = enemy_y + enemy.getGlobalBounds().height + 5.f;

  if (player_x < enemy_w &&
      player_w > enemy_x &&
      player_y > enemy_y &&
      player_h < enemy_h)
  {
    if (player_y > enemy_y && player_h > enemy_h)
    {
      return true;
    }
    return true;
  }
  return false;
}
void Functions::collectiblesAnim(
  sf::Sprite& collectible, sf::Clock& timer, float elapsed_time,
  sf::Vector2f& direction, float dt)
{
  if (timer.getElapsedTime().asSeconds() > elapsed_time)
  {
    direction.y = -direction.y;
    timer.restart();
  }
  collectible.move(0, direction.y * 15.f * dt);
}

bool Functions::insideText(sf::Event& event, sf::Text& text)
{
  if (event.mouseMove.x > text.getPosition().x &&
      event.mouseMove.x < text.getPosition().x + text.getGlobalBounds().width &&
      event.mouseMove.y  > text.getPosition().y &&
      event.mouseMove.y < text.getPosition().y + text.getGlobalBounds().height)
  {
    return true;
  }
  return false;
}
int Functions::centerTextX(sf::Text& text, int size_x)
{
  return size_x - text.getGlobalBounds().width / 2;
}

sf::Vector2f Functions::convertToWorld(sf::Vector2f vector)
{
  return vector = {vector.x / 16, vector.y / 16};
}
