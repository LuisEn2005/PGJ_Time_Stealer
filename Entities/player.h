#ifndef PLAYER_H
#define PLAYER_H
#include "../RaylibTools/raylibtools.h"

enum class PlayerAction {
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

    float actionTimer;
    float doubleTapTimer;

  public:
    Player(float x, float y);

    void Update(float deltaTime);
    void Draw() const;
    
    void SetAction(PlayerAction action, Color color);
    
    Vector2 GetPosition() const { return position; }
    PlayerAction GetCurrAction() const { return currAction; }
};

#endif //PLAYER_H
