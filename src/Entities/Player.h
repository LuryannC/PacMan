//
// Created by luria on 22/10/2022.
//
//
#ifndef PACMANSFML_PLAYER_H
#define PACMANSFML_PLAYER_H
#include "Entities.h"
#include "../Scripts/Functions.h"
#include "../GameObjects/TilesObject.h"
//#include "../Scripts/MapHandler.h"

#define right_vector {1,0}
#define left_vector {-1,0}
#define up_vector {0,-1}
#define down_vector {0,1}


class Player : public Entities
{

 public:
  Player(
    float x, float y, sf::RenderWindow& window,
    std::array<std::array<std::unique_ptr<TilesObject>, 30*34>, 3>& tile);
  void init();
  void update(float dt) override;
  void keyPressed(sf::Event& event, float dt) override;
  void render();
  void movePlayer(float dt);
  void rotateSprite();
  bool checkPath(sf::Vector2i vector);
  int playerPosAsID();
  int getLives() const;
  void setLives(int lives);
  void reset() override;
  void setMovement(const sf::Vector2i& movement);
  void setDesiredVector(const sf::Vector2i& desiredVector);
  void HandleAnimation();
  int getState() const;
  void setState(int state);

 private:
  int lives = 3;
  float spawn_x;
  float spawn_y;
  // Map related
  int tileID;
  int CELL_SIZE = 16;
  int MAP_WIDTH = 30;
  int MAP_HEIGHT = 34;
  int HALF_CELL = CELL_SIZE / 2;

  float scale_value = 1;
  sf::Vector2i movement;
  sf::Vector2i desired_vector;
  std::array<std::array<std::unique_ptr<TilesObject>, 30*34>, 3>& tile;
  sf::RectangleShape arrow;

  // Animation related
  sf::Clock animation_clock;
  sf::IntRect current_frame;

  int state;
  // Audio waka
  sf::Sound waka_audio;
  sf::SoundBuffer waka_buffer;
  sf::Clock song_elapsed;
  bool audio_started;
  int test;
};

#endif // PACMANSFML_PLAYER_H
