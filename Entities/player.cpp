#include "player.h"

Player::Player(float x, float y) 
  : position({ x, y }), size({ 40.0f, 60.0f }),
  currAction(PlayerAction::NONE), currColor(WHITE),
  actionTimer(0.0f), doubleTapTimer(0.0f) {}

  void Player::Update(float deltaTime) {
    // Decrementar temporizadores
    if (actionTimer > 0.0f) {
      actionTimer -= deltaTime;
      if (actionTimer <= 0.0f) {
        currAction = PlayerAction::NONE;
        currColor = WHITE; // Regresa al color normal
      }
    }

    if (doubleTapTimer > 0.0f) {
      doubleTapTimer -= deltaTime;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
      if (doubleTapTimer > 0.0f && currAction == PlayerAction::RED_ACTION) {
        SetAction(PlayerAction::BLUE_ACTION, BLUE);
        doubleTapTimer = 0.0f;
      } else {
        SetAction(PlayerAction::RED_ACTION, RED);
        doubleTapTimer = 0.25f;
      }
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
      SetAction(PlayerAction::GREEN_ACTION, GREEN);
    }
  }

void Player::SetAction(PlayerAction action, Color color){
  currAction = action;
  currColor = color;
  actionTimer = 0.4f;
}

void Player::Draw() const{
  DrawRectangleV(position, size, currColor);
  DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, 2, BLACK);
}
