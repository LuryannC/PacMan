//
// Created by luria on 22/10/2022.
//

#include "Player.h"
#include <cmath>


Player::Player(
  float x, float y, sf::RenderWindow& window,
  std::array<std::array<std::unique_ptr<TilesObject>, 30*34>, 3>&
    tile) :  Entities(x, y, window), tile(tile)
{
  velocity = 60.f;
  vector2F = {1,1};
  spawn_x = x;
  spawn_y = y;
  speed = 80.f;
}


void Player::init()
{
  Functions::generate(*sprite,
                      *texture,
                      "Data/Images/Pac-man-16-SpriteSheet.png",
                      tile[1][555]->getSprite()->getPosition().x,
                      tile[1][555]->getSprite()->getPosition().y,
                      scale_value,
                      scale_value);

  current_frame = sf::IntRect(0, 0, 16, 16);
  sprite->setTextureRect(sf::IntRect(current_frame));

  arrow.setSize(sf::Vector2f(2, 13));
  arrow.setFillColor(sf::Color::Red);
  arrow.setOrigin(1, 13);


  /// Audio
  if (!waka_buffer.loadFromFile("Data/Audio/Waka-Human.ogg"))
  {
    std::cout << "hit_buffer did not load" << std::endl;
  }

  waka_audio.setBuffer(waka_buffer);
  waka_audio.setVolume(80.f);

}
void Player::update(float dt)
{
  arrow.setPosition((sprite->getPosition().x + sprite->getGlobalBounds().width / 2), (sprite->getPosition().y + sprite->getGlobalBounds().height / 2));

  movePlayer(dt);

  if (static_cast<AnimationState>(state) != AnimationState::IDLE && !audio_started)
  {
    waka_audio.play();
    waka_audio.setLoop(true);
    audio_started = true;
  }
  if (song_elapsed.getElapsedTime().asSeconds() > 1.2f && static_cast<AnimationState>(state) == AnimationState::IDLE && audio_started)
  {
    waka_audio.stop();
    audio_started = false;
  }

  // Teleport edges
  if (playerPosAsID() == 479 && movement.x == 1)
  {
    sprite->setPosition(tile[1][450]->getSprite()->getPosition());
  }
  if (playerPosAsID() == 450 && movement.x == -1)
  {
    sprite->setPosition(tile[1][479]->getSprite()->getPosition());
  }
  //if (playerPosAsID() == 479 && (movement.x == 1 || (movement.y == 1 || movement.y == -1)))
//  if (sprite->getPosition().x + 2 >= 764 && movement.x == 1)
//  {
//    sprite->setPosition(tile[1][450]->getSprite()->getPosition());
//  }
//  if (sprite->getPosition().x - 2 >=  && movement.x == -1)
//  {
//    sprite->setPosition(tile[1][479]->getSprite()->getPosition());
//  }


  if (!destination.empty())
  {
    if (abs(sprite->getPosition().x - destination[0].x) < speed * 0.02f && abs(sprite->getPosition().y - destination[0].y) < speed * 0.02f)
    {
      sprite->setPosition(destination[0].x, destination[0].y);
      destination.erase(destination.begin());
    }
    sprite->move(direction.x * speed * dt, direction.y * speed * dt);
  }
}
void Player::render()
{
  window.draw(*sprite);
  //window.draw(arrow);
}
void Player::movePlayer(float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) /// Right
    {
      desired_vector = right_vector;
      arrow.setRotation(90);
      song_elapsed.restart();
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) /// Down
    {
      desired_vector = down_vector;
      arrow.setRotation(180);
      song_elapsed.restart();
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) /// Up
    {
      desired_vector = up_vector;
      arrow.setRotation(0);
      song_elapsed.restart();
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) /// Left
    {
      desired_vector = left_vector;
      arrow.setRotation(-90);
      song_elapsed.restart();
    }

  if (desired_vector != movement && !checkPath(movement))
  {
    movement = { 0, 0 };
  }
  else if (checkPath(desired_vector))
  {
    movement = desired_vector;
    if (desired_vector.x != 0)
    {
      //sprite->setPosition(sprite->getPosition().x, tile[1][tileID]->getSprite()->getPosition().y);
      sprite->setPosition(sprite->getPosition().x, lerpFunction(sprite->getPosition().y, tile[1][tileID]->getSprite()->getPosition().y, 0.2f));
    }
    if (desired_vector.y != 0)
    {
      //sprite->setPosition(tile[1][tileID]->getSprite()->getPosition().x, sprite->getPosition().y);
      sprite->setPosition(lerpFunction(sprite->getPosition().x, tile[1][tileID]->getSprite()->getPosition().x, 0.2f), sprite->getPosition().y);
    }
  }
  else if (movement == desired_vector && !checkPath(movement))
  {
    float gap_x = abs(sprite->getPosition().x - tile[1][tileID]->getSprite()->getPosition().x);
    float gap_y = abs(sprite->getPosition().y - tile[1][tileID]->getSprite()->getPosition().y);
    if (movement.x == 1 || movement.x == -1)
    {
      if (gap_x < 1)
      {
        movement = {0, 0};
      }
    }
    if (movement.y == 1 || movement.y == -1)
    {
      if (gap_y < 1)
      {
        movement = {0, 0};
      }
    }
  }

  if (movement.x == 0 && movement.y == 0)
  {
    sf::Vector2i next_pos(playerPosAsID() % MAP_WIDTH, int(playerPosAsID() / MAP_WIDTH));
    int index = int(next_pos.y) * MAP_WIDTH + int(next_pos.x);
    if (tile[1][index] != nullptr)
    {
      sprite->setPosition(lerpFunction(sprite->getPosition().x, tile[1][index]->getSprite()->getPosition().x, 0.2f), lerpFunction(sprite->getPosition().y, tile[1][index]->getSprite()->getPosition().y, 0.2f));
    }
  }

  sprite->move(movement.x * dt * speed, movement.y * dt * speed);

  rotateSprite();
  HandleAnimation();
}
void Player::keyPressed(sf::Event& event, float dt)
{
  Entities::keyPressed(event, dt);
}
void Player::rotateSprite()
{
  if (movement.x > 0) /// Left
  {
    sprite->setScale(scale_value, scale_value);
    sprite->setOrigin(0, 0);
  }
  else if (movement.x < 0) /// Right
  {
    sprite->setScale(-scale_value, scale_value);
    sprite->setOrigin(sprite->getGlobalBounds().width / scale_value, 0);
  }
}

bool Player::checkPath(sf::Vector2i vector)
{
  // Convert the player position + offset of the map into an ID
  // Then use the ID as location.
  int pos_x = (sprite->getPosition().x + HALF_CELL - int((window.getSize().x - (CELL_SIZE * MAP_WIDTH)) / 2)) / CELL_SIZE;
  int pos_y = (sprite->getPosition().y + HALF_CELL - int((window.getSize().y - (CELL_SIZE * MAP_HEIGHT)) / 2)) / CELL_SIZE;
  int next_pos_x = 0, next_pos_y = 0;


  next_pos_x = int(pos_x) + vector.x;
  next_pos_y = int(pos_y) + vector.y;
  int index = (next_pos_y) * MAP_WIDTH + (next_pos_x);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
  {
    std::cout << "pause\n";
  }

  if(tile[1][index] != nullptr)
  {
    if (tile[1][index]->getId() == 172)
    {
      tileID = index;
      return true;
    }
  }
  return false;
}

int Player::playerPosAsID()
{
  //return int((int((sprite->getPosition().y + 8) / 16) * 30) + int((sprite->getPosition().x + 8) / 16));
  return int((int((sprite->getPosition().y + HALF_CELL - int((window.getSize().y - (CELL_SIZE * MAP_HEIGHT)) / 2)) / CELL_SIZE) * MAP_WIDTH) + int((sprite->getPosition().x + HALF_CELL - int((window.getSize().x - (CELL_SIZE * MAP_WIDTH)) / 2)) / CELL_SIZE));
}
int Player::getLives() const
{
  return lives;
}
void Player::setLives(int lives)
{
  Player::lives = lives;
}
void Player::setMovement(const sf::Vector2i& movement)
{
  Player::movement = movement;
}
void Player::setDesiredVector(const sf::Vector2i& desiredVector)
{
  desired_vector = desiredVector;
}

void Player::reset()
{
  movement = {0,0};
  desired_vector = {0,0};
  sprite->setPosition( tile[1][555]->getSprite()->getPosition());
  lives = 3;
  waka_audio.stop();
  audio_started = false;
  Entities::reset();
}

void Player::HandleAnimation()
{
  if (abs(movement.x) > 0)
  {
    Functions::updateAnimation(*sprite,
                               animation_clock,
                               0.08f,
      static_cast<int>(AnimationState::MOVING),
                               current_frame,
                               64,
                               16);

    state = static_cast<int>(AnimationState::MOVING);
  }
  if (movement.y > 0)
  {
    Functions::updateAnimation(*sprite,
                               animation_clock,
                               0.08f,
                               static_cast<int>(AnimationState::MOVING_DOWN),
                               current_frame,
                               64,
                               16);
    state = static_cast<int>(AnimationState::MOVING_DOWN);
  }
  else if (movement.y < 0)
  {
    Functions::updateAnimation(*sprite,
                               animation_clock,
                               0.08f,
                               static_cast<int>(AnimationState::MOVING_UP),
                               current_frame,
                               64,
                               16);
    state = static_cast<int>(AnimationState::MOVING_UP);
  }
  else if (abs(movement.x) == 0 && abs(movement.y) == 0)
  {
    state = static_cast<int>(AnimationState::IDLE);
  }
  if (static_cast<AnimationState>(state) == AnimationState::DEAD)
  {
    Functions::updateAnimation(*sprite,
                               animation_clock,
                               0.08f,
                               static_cast<int>(AnimationState::DEAD),
                               current_frame,
                               48,
                               16);
    state = static_cast<int>(AnimationState::DEAD);
  }


}
int Player::getState() const
{
  return state;
}
void Player::setState(int state)
{
  Player::state = state;
}
