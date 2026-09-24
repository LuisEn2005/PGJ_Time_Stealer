#include "player.h"

Player::Player(float x, float y, Texture2D idle, Texture2D right, Texture2D up, Texture2D down) 
  : position({ x, y }), size({ 40.0f, 60.0f }), currAction(PlayerAction::NONE), currColor(WHITE), cooldownDuration(0.5f), texIdle(idle), texRight(right), texUp(up), texDown(down), currFrame(0), frameCounter(0.0f), frameSpeed(1.0f / 4.0f){
    TimerStart(&actionTimer, 0.0f);
    TimerStart(&cooldownTimer, 0.0f);

    actionTimer.finished = true;
    cooldownTimer.finished = true;

    currTex = texIdle;
    totalFrames = 6;
  }

void Player::Update(float deltaTime){
  TimerUpdate(&actionTimer);
  TimerUpdate(&cooldownTimer);

  frameCounter += deltaTime;
  if(frameCounter >= frameSpeed){
    frameCounter = 0.0f;
    currFrame = (currFrame + 1) % totalFrames;
  }

  if((TimerDone(&actionTimer)) && currAction == PlayerAction::RED_ACTION && TimerDone(&cooldownTimer)){
    TimerStart(&cooldownTimer, cooldownDuration);
  }

  if(TimerDone(&actionTimer) && currAction != PlayerAction::NONE){
    currAction = PlayerAction::NONE;
    currColor = WHITE;
    currTex = texIdle;
    totalFrames = 6;
    currFrame = 0;
    frameCounter = 0.0f;
  }

  if(TimerDone(&cooldownTimer)){
    if(IsKeyPressed(KEY_RIGHT)){
      SetAction(PlayerAction::RED_ACTION, RED, texRight, 13);
      TimerStart(&cooldownTimer, cooldownDuration);
    }
    if(IsKeyPressed(KEY_UP)){
      SetAction(PlayerAction::BLUE_ACTION, BLUE, texUp, 14);
      TimerStart(&cooldownTimer, cooldownDuration);
    }
    else if(IsKeyPressed(KEY_DOWN)){
      SetAction(PlayerAction::GREEN_ACTION, GREEN, texDown, 13);
      TimerStart(&cooldownTimer, cooldownDuration);
    }
  }
}

void Player::SetAction(PlayerAction action, Color color, Texture2D tex, int currTotalFrames){
  currAction = action;
  currColor = color;
  currTex = tex;
  totalFrames = currTotalFrames;
  currFrame = 0;
  frameCounter = 0.0f;

  TimerStart(&actionTimer, 0.2f);
}

void Player::Draw() const{
  DrawRectangleV(position, size, currColor);
  DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, 2, BLACK);

  if(currTex.id > 0){
    float frameWidth = (float)currTex.width / totalFrames;
    float frameHeight = (float)currTex.height;
    Rectangle srcRec = { currFrame * frameWidth, 0.0f, frameWidth, frameHeight };

    float drawX = position.x + (size.x - frameWidth) / 2.0f;
    float drawY = (position.y + size.y) - frameHeight + 20.0f;

    Rectangle destRec = { drawX, drawY, frameWidth, frameHeight };

    DrawTexturePro(currTex, srcRec, destRec, { 0.0f, 0.0f }, 0.0f, WHITE);
  }
}
