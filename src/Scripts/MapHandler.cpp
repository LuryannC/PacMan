//
// Created by luria on 16/10/2022.
//
#include <iostream>
#include "MapHandler.h"
#include <memory>


MapHandler::MapHandler(sf::RenderWindow& window) : window(window)
{

}

bool MapHandler::init()
{
  texture.loadFromFile("Data/TileMap/tiles set.png");
  loadMap();
  return true;
}

sf::IntRect MapHandler::makeTextureRect(int tile_ID, int sheet_size_x, int cell_size)
{
  int left = 0;
  int top = 0;

  for (int i = 0; i < tile_ID; ++i)
  {
    left++;
    if (left == sheet_size_x)
    {
      left = 0;
      top++;
    }
  }
  left = left * cell_size;
  top = top * cell_size;
  textureRect.height = cell_size;
  textureRect.left = left;
  textureRect.top = top;
  textureRect.width = cell_size;
  //std::cout << ID;
  //std::cout << "L: " + std::to_string(left) + "T: " + std::to_string(top);
  //std::cout << " , ";

  return textureRect;
}

void MapHandler::loadMap()
{
  map.load("Data/TileMap/TestIDMap.tmx");
  const auto& layers=map.getLayers();
  int k = 0;
  for (auto& layer: layers)
  {
    const auto& current_layer_tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
    for (int i = 0; i < layer->getSize().y; ++i)
    {
      for (int j = 0; j < layer->getSize().x; ++j)
      {
        if (current_layer_tiles[i * layer->getSize().x + j].ID > 0)
        {
          tile[k][i * layer->getSize().x + j] = (std::make_unique<TilesObject>(0,0, window, current_layer_tiles[i * layer->getSize().x + j].ID));
          //sprite[k][i * layer->getSize().x + j]->getSprite()->setOrigin(8,8);
          if (layer->getVisible())
          {
            tile[k][i * layer->getSize().x + j]->getSprite()->setTexture(texture);
            tile[k][i * layer->getSize().x + j]->getSprite()->setTextureRect(makeTextureRect(current_layer_tiles[i * layer->getSize().x + j].ID - 1, 22, CELL_SIZE));
          }
//          sprite[k][i * layer->getSize().x + j]->getSprite()->setPosition(
//            float(CELL_SIZE) * j,
//            float(CELL_SIZE) * i);
          tile[k][i * layer->getSize().x + j]->getSprite()->setPosition(
            float(CELL_SIZE) * j + ((window.getSize().x - (CELL_SIZE * layer->getSize().x)) / 2),
            float(CELL_SIZE) * i + ((window.getSize().y - (CELL_SIZE * layer->getSize().y)) / 2));

          /// Set the cost to the tiles
          switch (k)
          {
            case 0:
              tile[k][i * layer->getSize().x + j]->setCost(10);
              map_costs[i * layer->getSize().x + j] = 10;
              break ;
            case 1:
              tile[k][i * layer->getSize().x + j]->setCost(0);
              map_costs[i * layer->getSize().x + j] = 0;
              break;
            case 2:
              tile[k][i * layer->getSize().x + j]->setCost(0);
              map_costs[i * layer->getSize().x + j] = 0;
          }
        }
        else
        {
          tile[k][i * layer->getSize().x + j] = nullptr;
        }
      }
    }
    k++;
  }
}

sf::Vector2i MapHandler::vectorToId(sf::Vector2i vector)
{
  return {(vector.x - (int(window.getSize().x - (CELL_SIZE * MAP_WIDTH)) / 2)) / CELL_SIZE, (vector.y - (int(window.getSize().y - (CELL_SIZE * MAP_HEIGHT)) / 2)) / CELL_SIZE};
}

int MapHandler::toIndex(sf::Vector2i vector)
{
  return int((int((vector.y + HALF_CELL - int((window.getSize().y - (CELL_SIZE * MAP_HEIGHT)) / 2)) / CELL_SIZE) * MAP_WIDTH) + int((vector.x + HALF_CELL - int((window.getSize().x - (CELL_SIZE * MAP_WIDTH)) / 2)) / CELL_SIZE));
}
sf::Vector2i MapHandler::getDistance(sf::Vector2i start, sf::Vector2i end)
{
  return { abs(start.x - end.x), abs(start.y - end.y) };
}
int MapHandler::returnCost(int index)
{
  return map_costs[index];
}

sf::Vector2f MapHandler::toWorld(sf::Vector2i vector)
{
  return {float(vector.x * CELL_SIZE + (int(window.getSize().x - (CELL_SIZE * MAP_WIDTH)) / 2)),float(vector.y * CELL_SIZE + (int(window.getSize().y - (CELL_SIZE * MAP_HEIGHT)) / 2))};
}