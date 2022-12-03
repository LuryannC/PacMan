//
// Created by luria on 07/11/2022.
//

#ifndef PACMANSFML_LEADERBOARD_H
#define PACMANSFML_LEADERBOARD_H

#include <fstream>
#include <iostream>
#include <memory>
#include "vector"
#include "array"

class Leaderboard
{
 public:
  Leaderboard();
  void AddToLeaderboard(std::string name, int score);
  void SortList();

 private:
  static const int size = 2;
  std::array<std::string, size> names;
  //std::vector<std::array<std::string, size>> scoreboard;
  std::vector<std::tuple<std::string, int>> scoreboard;

};

#endif // PACMANSFML_LEADERBOARD_H
