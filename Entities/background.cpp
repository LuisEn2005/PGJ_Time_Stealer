#include "background.h"

Background::Background(Texture2D farTexture, Texture2D midTexture, Texture2D gameplayTexture, float width, float height) : farBg(farTexture), midBg(midTexture), gameplayBg(gameplayTexture), farOffset(0.0f), midOffset(0.0f), gameplayOffset(0.0f), screenWidth(width), screenHeight(height) {}

void Background::Update(float deltaTime, float gameSpeed){
  farOffset -= (gameSpeed * 0.1f) * deltaTime;
  if(farOffset <= -farBg.width) farOffset = 0.0f;

  midOffset -= (gameSpeed * 0.3f) * deltaTime;
  if(midOffset <= -midBg.width) midOffset = 0.0f;
  
  gameplayOffset -= gameSpeed * deltaTime;
  if(gameplayOffset <= -gameplayBg.width) gameplayOffset = 0.0f;
}

void Background::Draw() const{
  DrawTextureEx(farBg, {farOffset, 0.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(farBg, {farOffset + farBg.width, 0.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(farBg, {farOffset + farBg.width + farBg.width, 0.0f}, 0.0f, 1.0f, WHITE);
  
  DrawTextureEx(midBg, {midOffset, 90.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(midBg, {midOffset + midBg.width, 90.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(midBg, {midOffset + midBg.width + midBg.width, 90.0f}, 0.0f, 1.0f, WHITE);

  DrawTextureEx(gameplayBg, {gameplayOffset, 240.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(gameplayBg, {gameplayOffset + gameplayBg.width, 240.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(gameplayBg, {gameplayOffset + gameplayBg.width + gameplayBg.width, 24.0f}, 0.0f, 1.0f, WHITE);
}
