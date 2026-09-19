#include "RaylibTools/raylibtools.h"
#include <vector>
#include "Entities/player.h"
#include "Entities/obstacle.h"
#include <cstdlib>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Time Stealer");
  SetTargetFPS(60);

  float floorY = 550.0f;

  Player player(150, floorY - 60.0f);

  std::vector<Obstacle> obstaculos;
  obstaculos.push_back(Obstacle(700, floorY, ObstacleType::BAJO));
  obstaculos.push_back(Obstacle(1100, floorY, ObstacleType::DOBLE_BAJO));
  obstaculos.push_back(Obstacle(1500, floorY, ObstacleType::ALTO));
  bool gameOver = false;
  float gameSpeed = 300.0f;

  Timer spawnTimer;
  TimerStart(&spawnTimer, 1.5f);

  while(!WindowShouldClose()){
    float deltaTime = GetFrameTime();

    if(!gameOver){
      player.Update(deltaTime);

      TimerUpdate(&spawnTimer);

      if(TimerDone(&spawnTimer)){
        ObstacleType type = static_cast<ObstacleType>(rand() % 3);
        obstaculos.push_back(Obstacle(900.0f, floorY, type));

        float nextSpawnTime = 1.2f + ((float)rand() / RAND_MAX) * 0.8f;
        TimerStart(&spawnTimer, nextSpawnTime);
      }

      for(auto& obs : obstaculos){
        obs.Update(deltaTime, gameSpeed);

        if (obs.IsCleared()) continue;

        float dist = obs.GetPosition().x - player.GetPosition().x;

        if(dist > 20.0f && dist < 110.0f){
          if(obs.GetType() == ObstacleType::BAJO && player.GetCurrAction() == PlayerAction::RED_ACTION){
            obs.SetCleared(true);
          }
          else if(obs.GetType() == ObstacleType::DOBLE_BAJO && player.GetCurrAction() == PlayerAction::BLUE_ACTION){
            obs.SetCleared(true);
          }
          else if(obs.GetType() == ObstacleType::ALTO && player.GetCurrAction() == PlayerAction::GREEN_ACTION){
            obs.SetCleared(true);
          }
        }
        else if(dist <= 20.0f && !obs.IsCleared()){
          gameOver = true;
        }
      }

      for(size_t i = 0; i < obstaculos.size(); ){
        if (obstaculos[i].IsOffScreen()) {
          obstaculos.erase(obstaculos.begin() + i);
        } else {
          i++;
        }
      }      
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawLine(0, (int)floorY, 800, (int)floorY, DARKGRAY);

    DrawRectangle(150 + 20, 0, 90, 600, Fade(YELLOW, 0.15f));

    for (const auto& obs : obstaculos) {
      obs.Draw();
    }
    player.Draw();

    if (gameOver) {
      DrawText("¡GAME OVER! Fallaste la accion", 240, 280, 25, RED);
    } else {
      DrawText("Rojo: UP | Azul: UP x2 | Verde: DOWN", 10, 10, 20, BLACK);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
