#include "player.h"

Player::Player(float x, float y) 
  : position({ x, y }), size({ 40.0f, 60.0f }), currAction(PlayerAction::NONE), currColor(WHITE), cooldownDuration(0.5f){
    TimerStart(&actionTimer, 0.0f);
    TimerStart(&cooldownTimer, 0.0f);

    actionTimer.finished = true;
    cooldownTimer.finished = true;
  }

void Player::Update(float deltaTime){
  TimerUpdate(&actionTimer);
  TimerUpdate(&cooldownTimer);

  if((TimerDone(&actionTimer)) && currAction == PlayerAction::RED_ACTION && TimerDone(&cooldownTimer)){
    TimerStart(&cooldownTimer, cooldownDuration);
  }

  if(TimerDone(&actionTimer) && currAction != PlayerAction::NONE){
    currAction = PlayerAction::NONE;
    currColor = WHITE;
  }

  if(TimerDone(&cooldownTimer)){
    if(IsKeyPressed(KEY_RIGHT)){
      SetAction(PlayerAction::RED_ACTION, RED);
      TimerStart(&cooldownTimer, cooldownDuration);
    }
    if(IsKeyPressed(KEY_UP)){
      SetAction(PlayerAction::BLUE_ACTION, BLUE);
      TimerStart(&cooldownTimer, cooldownDuration);
    }
    else if(IsKeyPressed(KEY_DOWN)){
      SetAction(PlayerAction::GREEN_ACTION, GREEN);
      TimerStart(&cooldownTimer, cooldownDuration);
    }
  }
}

void Player::SetAction(PlayerAction action, Color color){
  currAction = action;
  currColor = color;
  TimerStart(&actionTimer, 0.2f);
}

void Player::Draw() const{
  DrawRectangleV(position, size, currColor);
  DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, 2, BLACK);
}
