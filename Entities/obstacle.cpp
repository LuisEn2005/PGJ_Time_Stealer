#include "obstacle.h"

Obstacle::Obstacle(float x, float floorY, ObstacleType type) 
  : type(type), isCleared(false) 
{
  float blockSize = 40.0f;

  switch(type){
    case ObstacleType::BAJO:
      size = { blockSize, blockSize };
      position = { x, floorY - size.y };
      color = RED;
      break;

    case ObstacleType::DOBLE_BAJO:
      size = { blockSize, blockSize * 2.0f };
      position = { x, floorY - size.y };
      color = BLUE;
      break;

    case ObstacleType::ALTO:
      size = { blockSize * 1.5f, blockSize };
      position = { x, floorY - 70.0f };
      color = GREEN;
      break;
  }
}

void Obstacle::Update(float deltaTime, float gameSpeed){
    position.x -= gameSpeed * deltaTime;
}

void Obstacle::Draw() const{
  Color drawColor = isCleared ? GRAY : color;
  DrawRectangleV(position, size, drawColor);
  DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, 2, BLACK);
}
