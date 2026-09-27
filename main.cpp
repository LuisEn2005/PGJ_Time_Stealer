#include "RaylibTools/raylibtools.h"
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Entities/player.h"
#include "Entities/obstacle.h"
#include "Entities/background.h"

enum GameScreen{
  STATE_PROLOGO,
  STATE_TUTORIAL,
  STATE_GAMEPLAY,
  STATE_GAMEOVER
};

int main(void){
  srand(time(0));
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Ladron Del Tiempo");

  int playerScore = 0;
  Text finalScore;
  InitAudioDevice();

  Music musicGame = LoadMusicStream("./music/ladrondeltiempo.wav");
  Sound deathSound = LoadSound("./music/Hitsound.wav");
  Sound jumpSound = LoadSound("./music/jumpsound.wav");

  Texture2D tutorialTex = LoadTexture("./sprites/tutorial.png");
  Texture2D prologoTex = LoadTexture("./sprites/prologo.png");

  SetTargetFPS(60);

  float floorY = 550.0f;

  Texture2D texIdle = LoadTexture("./Entities/playerSprites/idle_move.png");
  Texture2D texRight = LoadTexture("./Entities/playerSprites/right_move.png");
  Texture2D texUp = LoadTexture("./Entities/playerSprites/up_move.png");
  Texture2D texDown = LoadTexture("./Entities/playerSprites/down_move.png");
  Player player(150, floorY - 60.0f, texIdle, texRight, texUp, texDown);

  std::vector<Obstacle> obstaculos;

  bool gameOver = false;
  bool gameWon = false;
  float gameSpeed = 300.0f;
  const int MAX_SCORE = 500;

  Texture2D clava_tex = LoadTexture("./Entities/obsSprites/clava_pairs.png");
  Texture2D farBgTex = LoadTexture("./sprites/Background2.png");
  Texture2D midBgTex = LoadTexture("./sprites/Background1.png");
  Texture2D gameplayBgTex = LoadTexture("./sprites/Background.png");

  Background background(farBgTex, midBgTex, gameplayBgTex, 800, 150);
  Rectangle rec = { player.GetPosition().x + 40, 0, 50, 600 };

  int simpleVar, highVar;

  Timer spawnTimer;
  TimerStart(&spawnTimer, 1.5f);

  GameScreen currScreen = STATE_PROLOGO;
  
  TextureButton buttonRestart;
  TextureButton buttonExit;
  Rectangle btnCloseTut = { 6, 6, 80, 80 };

  MakeTextureButton(&buttonRestart, RectangleBounds(400, 300, 100, 30), "./sprites/boton_reiniciar.png");
  MakeTextureButton(&buttonExit, RectangleBounds(400, 340, 100, 30), "./sprites/boton_salir.png");

  PlayMusicStream(musicGame);

  while(!WindowShouldClose()){
    float deltaTime = GetFrameTime();
    Vector2 mousePoint = GetMousePosition();

    switch(currScreen){
      case STATE_PROLOGO:{
        if(IsKeyPressed(KEY_ENTER)){
          currScreen = STATE_TUTORIAL;
        }

      } break;
      case STATE_TUTORIAL:{
        bool clickedCloseX = CheckCollisionPointRec(mousePoint, btnCloseTut) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        if(clickedCloseX){
          currScreen = STATE_GAMEPLAY;
          PlayMusicStream(musicGame);
        }
      } break;
      case STATE_GAMEPLAY:{
        UpdateMusicStream(musicGame);
        finalScore = MakeText(TextFormat("Puntuacion: %i", playerScore), 40, BLACK);
        
        if(playerScore >= MAX_SCORE){
          gameWon = true;
          currScreen = STATE_GAMEOVER;
          StopMusicStream(musicGame);
        }
        
        background.Update(deltaTime, gameSpeed);
        player.Update(deltaTime);

        TimerUpdate(&spawnTimer);
        if(TimerDone(&spawnTimer)){
          ObstacleType type = static_cast<ObstacleType>(rand() % 3);
          if(type == ObstacleType::UP){
            highVar = rand() % 16;
            obstaculos.push_back(Obstacle(900.0f, floorY, type, clava_tex, highVar));
          } else{
            simpleVar = rand() % 4; 
            obstaculos.push_back(Obstacle(900.0f, floorY, type, clava_tex, simpleVar));
          }

          float nextSpawnTime = 1.0f + ((float)rand() / RAND_MAX) * 0.8f;
          TimerStart(&spawnTimer, nextSpawnTime);
        }

        for(auto& obs : obstaculos){
          obs.Update(deltaTime, gameSpeed);

          if(obs.IsCleared()) continue;

          float dist = obs.GetPosition().x - player.GetPosition().x;

          if(dist > 40.0f && dist < rec.width + 40.0f){
            if(obs.GetType() == ObstacleType::RIGHT && player.GetCurrAction() == PlayerAction::RED_ACTION){
              obs.SetCleared(true);
              PlaySound(jumpSound);
              playerScore += 10;
            }
            else if(obs.GetType() == ObstacleType::UP && player.GetCurrAction() == PlayerAction::BLUE_ACTION){
              obs.SetCleared(true);
              PlaySound(jumpSound);
              playerScore += 10;
            }
            else if(obs.GetType() == ObstacleType::DOWN && player.GetCurrAction() == PlayerAction::GREEN_ACTION){
              obs.SetCleared(true);
              PlaySound(jumpSound);
              playerScore += 10;
            }
          }
          else if(dist <= 40.0f && !obs.IsCleared()){
            PlaySound(deathSound);
            gameOver = true;
            currScreen = STATE_GAMEOVER;
            StopMusicStream(musicGame);
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
      break;
      case STATE_GAMEOVER:{
        if(HandleTextureButton(&buttonRestart)){
          playerScore = 0;
          gameOver = false;
          gameWon = false;
          obstaculos.clear();
          TimerStart(&spawnTimer, 1.5f);

          PlayMusicStream(musicGame);
          currScreen = STATE_GAMEPLAY;
        }
        if (HandleTextureButton(&buttonExit)) {
          UnloadMusicStream(musicGame);
          UnloadSound(jumpSound);
          UnloadSound(deathSound);

          CloseAudioDevice();
          
          UnloadTexture(tutorialTex);
          UnloadTexture(prologoTex);
          UnloadTexture(texIdle);
          UnloadTexture(texRight);
          UnloadTexture(texUp);
          UnloadTexture(texDown);
          UnloadTexture(clava_tex);
          UnloadTexture(farBgTex);
          UnloadTexture(midBgTex);
          UnloadTexture(gameplayBgTex);
          CloseWindow();
          return 0;
        }
      }
      break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if(currScreen == STATE_PROLOGO){
      DrawTexturePro(prologoTex,
          (Rectangle){ 0, 0, (float)prologoTex.width, (float)prologoTex.height },
          (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
          (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    else if(currScreen == STATE_TUTORIAL){
      DrawTexturePro(tutorialTex,
          (Rectangle){ 0, 0, (float)tutorialTex.width, (float)tutorialTex.height },
          (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
          (Vector2){ 0, 0 }, 0.0f, WHITE);
      CheckCollisionPointRec(mousePoint, btnCloseTut) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
    else{
      DrawLine(0, (int)floorY, 800, (int)floorY, DARKGRAY);

      background.Draw();

      for(const auto& obs : obstaculos){
        obs.Draw();
      }
      player.Draw();
    }
    if(currScreen == STATE_GAMEPLAY){
      DrawText(finalScore.text, 300, 10, finalScore.fontSize, finalScore.textColor);
    }
    if(currScreen == STATE_GAMEOVER){
      if(gameOver){
        DrawText("El ladron logro burlarte", 220, 220, 30, RED);
      }
      else if(gameWon){
        DrawText("Atrapaste al ladron del tiempo", 180, 220, 30, BLUE);
      }

      DrawText(finalScore.text, 250, 250, finalScore.fontSize, RAYWHITE);
      DrawTextureButton(&buttonRestart);
      DrawTextureButton(&buttonExit);
    }

    EndDrawing();
  }

  UnloadMusicStream(musicGame);
  UnloadSound(jumpSound);
  UnloadSound(deathSound);

  CloseAudioDevice();

  UnloadTexture(tutorialTex);
  UnloadTexture(prologoTex);
  UnloadTexture(texIdle);
  UnloadTexture(texRight);
  UnloadTexture(texUp);
  UnloadTexture(texDown);
  UnloadTexture(clava_tex);
  UnloadTexture(farBgTex);
  UnloadTexture(midBgTex);
  UnloadTexture(gameplayBgTex);

  CloseWindow();
  return 0;
}
