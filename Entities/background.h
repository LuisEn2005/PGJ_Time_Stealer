#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../RaylibTools/raylibtools.h"

class Background{
  private:
    Texture2D farBg;
    Texture2D midBg;
    Texture2D gameplayBg;

    float farOffset;
    float midOffset;
    float gameplayOffset;

    float screenWidth;
    float screenHeight;

  public:
    Background(Texture2D farTexture, Texture2D midTexture, Texture2D gameplayTexture, float width, float height);
    void Update(float deltaTime, float gameSpeed);
    void Draw() const;
};

#endif //BACKGROUND_H
