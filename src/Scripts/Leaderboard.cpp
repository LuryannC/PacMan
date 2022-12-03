//
// Created by luria on 07/11/2022.
//

#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
//  std::ifstream file("Data/leaderboards.json");
//  Json::Reader reader;
//  Json::Value completeJsonData;
//  reader.parse(file, completeJsonData);
//  std::cout << completeJsonData[0][0] << std::endl;
}

void Leaderboard::AddToLeaderboard(std::string name, int score)
{
  scoreboard.emplace_back(name, score);
}
void Leaderboard::SortList()
{

}