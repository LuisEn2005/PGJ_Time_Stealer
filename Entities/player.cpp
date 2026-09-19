#include "player.h"

Player::Player(float x, float y) 
  : position({ x, y }), size({ 40.0f, 60.0f }),
  currAction(PlayerAction::NONE), currColor(WHITE){
    TimerStart(&actionTimer, 0.0f);
    TimerStart(&doubleTapTimer, 0.0f);
    actionTimer.finished = true;
    doubleTapTimer.finished = true;
  }

void Player::Update(float deltaTime){
  TimerUpdate(&actionTimer);
  TimerUpdate(&doubleTapTimer);

  if(TimerDone(&actionTimer) && currAction != PlayerAction::NONE){
    currAction = PlayerAction::NONE;
    currColor = WHITE;
  }
  if(IsKeyPressed(KEY_UP)){
    if(!TimerDone(&doubleTapTimer) && currAction == PlayerAction::RED_ACTION){
      SetAction(PlayerAction::BLUE_ACTION, BLUE);
      doubleTapTimer.finished = true;
    } else {
      SetAction(PlayerAction::RED_ACTION, RED);
      TimerStart(&doubleTapTimer, 0.25f);
    }
  }
  else if(IsKeyPressed(KEY_DOWN)){
    SetAction(PlayerAction::GREEN_ACTION, GREEN);
  }
}

void Player::SetAction(PlayerAction action, Color color){
  currAction = action;
  currColor = color;
  TimerStart(&actionTimer, 0.4f);
}

void Player::Draw() const{
  DrawRectangleV(position, size, currColor);
  DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, 2, BLACK);
}
