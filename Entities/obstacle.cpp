#include "obstacle.h"

Obstacle::Obstacle(float x, float floorY, ObstacleType type, Texture2D tex, int variant) 
  : type(type), isCleared(false), texture(tex)
{
  float blockSize = 40.0f;

  switch(type){
    case ObstacleType::BAJO:
      size = { blockSize, blockSize };
      position = { x, floorY - size.y };
      color = RED;
      srcRec = { (variant % 4) * 40.0f, 40.0f, 40.0f, 40.0f };
      break;

    case ObstacleType::DOBLE_BAJO:
      size = { blockSize, blockSize * 2.0f };
      position = { x, floorY - size.y };
      color = BLUE;
      srcRec = { (variant % 16) * 40.0f, 0.0f, 40.0f, 80.0f };
      break;

    case ObstacleType::ALTO:
      size = { blockSize, blockSize };
      position = { x, floorY - 70.0f };
      color = GREEN;
      srcRec = { (variant % 4) * 40.0f, 40.0f, 40.0f, 40.0f };
      break;
  }
}

void Obstacle::Update(float deltaTime, float gameSpeed){
  position.x -= gameSpeed * deltaTime;
}

void Obstacle::Draw() const{
  Color drawColor = isCleared ? GRAY : WHITE;
  Rectangle destRec = { position.x, position.y, size.x, size.y }; 
  DrawTexturePro(texture, srcRec, destRec, { 0.0f, 0.0f }, 0.0f, drawColor);


  DrawRectangleLinesEx(destRec, 2, color);
}
