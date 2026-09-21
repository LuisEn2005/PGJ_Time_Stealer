#include "background.h"

Background::Background(Texture2D farTexture, Texture2D midTexture, float width, float height) : farBg(farTexture), midBg(midTexture), farOffset(0.0f), midOffset(0.0f), screenWidth(width), screenHeight(height) {}

void Background::Update(float deltaTime, float gameSpeed){
  farOffset -= (gameSpeed * 0.1f) * deltaTime;
  if(farOffset <= -farBg.width) farOffset = 0.0f;
}

void Background::Draw() const{
  DrawTextureEx(farBg, {farOffset, 0.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(farBg, {farOffset + farBg.width, 0.0f}, 0.0f, 1.0f, WHITE);
  DrawTextureEx(farBg, {farOffset + farBg.width + farBg.width, 0.0f}, 0.0f, 1.0f, WHITE);
}
