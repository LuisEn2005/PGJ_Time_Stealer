#ifndef PLAYER_H
#define PLAYER_H
#include "../RaylibTools/raylibtools.h"

enum class PlayerAction{
  NONE,
  RED_ACTION,
  BLUE_ACTION,
  GREEN_ACTION
};

class Player{
  private:
    Vector2 position;
    Vector2 size;
    PlayerAction currAction;
    Color currColor;

    Timer actionTimer;
    Timer cooldownTimer;

    float cooldownDuration;

    Texture2D texIdle;
    Texture2D texRight;
    Texture2D texUp;
    Texture2D texDown;
  
    Texture2D currTex;
    int totalFrames;
    int currFrame;
    int frameCounter;
    int frameSpeed;
  public:
    Player(float x, float y, Texture2D idle, Texture2D right, Texture2D up, Texture2D down);

    void Update(float deltaTime);
    void Draw() const;

    void SetAction(PlayerAction action, Color color, Texture2D tex, int currTotalFrames);

    Vector2 GetPosition() const { return position; }
    PlayerAction GetCurrAction() const { return currAction; }
};

#endif //PLAYER_H
