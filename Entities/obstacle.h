#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../RaylibTools/raylibtools.h"

enum class ObstacleType {
  BAJO,
  DOBLE_BAJO,
  ALTO
};

class Obstacle {
  private:
    Vector2 position;
    Vector2 size;
    ObstacleType type;
    Color color;
    bool isCleared;

    Texture2D texture;
    Rectangle srcRec;
    Rectangle extraRec;
  public:
    Obstacle(float x, float floorY, ObstacleType type, Texture2D tex, int variant);

    void Update(float deltaTime, float gameSpeed);
    void Draw() const;

    Vector2 GetPosition() const { return position; }
    ObstacleType GetType() const { return type; }

    bool IsCleared() const { return isCleared; }
    void SetCleared(bool value) { isCleared = value; }

    bool IsOffScreen() const { return position.x < -100.0f; }
};

#endif // OBSTACLE_H
