//
// Created by luria on 09/11/2022.
//

#ifndef PACMANSFML_PATHFINDING_H
#define PACMANSFML_PATHFINDING_H

#include "MapHandler.h"
#include <utility>
#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>
#include <queue>

namespace std
{
  template<> struct hash<sf::Vector2i>
  {
    std::size_t operator()(const sf::Vector2i& id) const noexcept
    {
      return id.x * id.y;
    }
  };
}

using std::vector;
using std::pair;
using PQElement = pair<int,pair<int,int>>;
std::vector<sf::Vector2i> get_neighbours(MapHandler& mapHandler, const sf::Vector2i& node, int map_width, int map_height);
inline double heuristic(const sf::Vector2i& a, const sf::Vector2i& b);
void a_star(MapHandler& mapHandler, sf::Vector2i& start, sf::Vector2i& end, std::unordered_map<sf::Vector2i, sf::Vector2i>& came_from, std::unordered_map<sf::Vector2i , int>& cost_so_far);
struct PriorityQueue
{

  std::priority_queue<PQElement, vector<PQElement>, std::greater<PQElement>> elements;

  inline bool empty() const {return elements.empty(); }

  inline void put(pair<int,int> item, int priority) {elements.emplace(priority, item); }

  pair<int,int> get()
  {
    pair<int,int> best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};


vector<sf::Vector2f> Pathfinder(MapHandler& mapHandler, sf::Vector2i& end, sf::Sprite& entity);
vector<sf::Vector2i> ReconstructPath(sf::Vector2i start,sf::Vector2i end,std::unordered_map<sf::Vector2i, sf::Vector2i>& came_from);


//int tile_index;
//int CELL_SIZE = 16;
//int MAP_WIDTH = 30;
//int MAP_HEIGHT = 34;
//int HALF_CELL = CELL_SIZE / 2;

#endif // PACMANSFML_PATHFINDING_H
