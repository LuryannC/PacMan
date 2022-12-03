//
// Created by luria on 09/11/2022.
//

#include "Pathfinding.h"


std::vector<sf::Vector2i> get_neighbours(MapHandler& mapHandler, const sf::Vector2i& node, int map_width, int map_height)
{
  std::vector<sf::Vector2i> neighbours;

  const int TILE_TO_CHECK = 4;

  sf::Vector2i available_tiles[TILE_TO_CHECK] =
    {
      {0,-1},
      {0, 1},
      {-1, 0},
      {1, 0}
    };


  for (int i = 0; i < TILE_TO_CHECK; ++i)
  {
    sf::Vector2i new_pos(node.x + available_tiles[i].x, node.y + available_tiles[i].y);
    //int index =  mapHandler.toIndex(new_pos);

    if (new_pos.x > map_width - 1 || new_pos.x < 0 || new_pos.y > map_height - 1 || new_pos.y < 0)
      continue ;

    if (mapHandler.returnCost(new_pos.y * map_width + new_pos.x) > 0)
      continue ;

    //tile_index = index;
    neighbours.push_back(new_pos);
  }

  return neighbours;
}

inline double heuristic(const sf::Vector2i& a, const sf::Vector2i& b)
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void a_star(MapHandler& mapHandler, sf::Vector2i& start, sf::Vector2i& end,
            std::unordered_map<sf::Vector2i, sf::Vector2i>& came_from,
            std::unordered_map<sf::Vector2i, int>& cost_so_far)
{
  PriorityQueue frontier;
  pair<int,int> test(start.x,start.y);
  frontier.put(test, 0);
  //auto cost_map = map.getCostOfWalls();
  came_from[start] = start;
  cost_so_far[start] = 0;

  while (!frontier.empty())
  {
    pair<int,int> temp = frontier.get();
    sf::Vector2i  current = {temp.first,temp.second};

    if (current.x == end.x && current.y == end.y)
    {
      break;
    }

    for (sf::Vector2i next : get_neighbours(mapHandler, current, 30, 34))
    {
      //int new_cost = mapHandler.returnCost(mapHandler.toIndex(next));
      int new_cost = mapHandler.returnCost(next.x * 30 + next.y);
      if(cost_so_far.find(next) == cost_so_far.end()|| new_cost < cost_so_far[next] )
      {
        cost_so_far[next] = new_cost;
        int priority = new_cost + heuristic(next,end);
        pair<int,int> Next(next.x,next.y);
        frontier.put(Next,priority);
        came_from[next] = current;
      }
    }
  }
}

vector<sf::Vector2f> Pathfinder(MapHandler& mapHandler, sf::Vector2i& end, sf::Sprite& entity)
{
  sf::Vector2i tile_loc(mapHandler.vectorToId(end));
  //int tile_cost = mapHandler.tile[1][mapHandler.toIndex(tile_loc)]->getCost();
  int tile_cost = mapHandler.returnCost(tile_loc.y * 30 + tile_loc.x);

  vector<sf::Vector2f> tiles_to_visit;
  tiles_to_visit.reserve(50);

  sf::Vector2i player_pos(entity.getPosition().x + entity.getGlobalBounds().width/2,
                          entity.getPosition().y + entity.getGlobalBounds().height/2);

  sf::Vector2i start(mapHandler.vectorToId(player_pos));

  std::unordered_map<sf::Vector2i,sf::Vector2i> came_from;
  std::unordered_map<sf::Vector2i,int> cost_so_far;

  if (tile_cost < 1)
  {
    a_star(mapHandler, start, tile_loc, came_from, cost_so_far);
    for (auto loc : ReconstructPath(start,tile_loc,came_from))
    {
      tiles_to_visit.push_back(mapHandler.toWorld(loc));
    }
  }
  return tiles_to_visit;
}

vector<sf::Vector2i> ReconstructPath(
  sf::Vector2i start, sf::Vector2i end,
  std::unordered_map<sf::Vector2i, sf::Vector2i>& came_from)
{
  sf::Vector2i current = end;
  vector <sf::Vector2i> path;
  while (current != start)
  {
    path.push_back(current);
    current = came_from[current];
  }

  //path.push_back(start);
  std::reverse(path.begin(),path.end());
  return path;
}

