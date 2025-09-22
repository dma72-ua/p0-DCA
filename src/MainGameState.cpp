#include "MainGameState.hpp"
#include "GameOverState.hpp"
#include "StateMachine.hpp"
#include <iostream>
#include <string>
#include <vector>

MainGameState::MainGameState() {
  player.x = 200;
  player.y = 200;
  gravedad = 400;
  playerPoints = 0;
}

void MainGameState::init() {
  birdSprite = std::vector<Texture2D>(3);
  birdSprite[0] = LoadTexture("assets/yellowbird-upflap.png");
  birdSprite[1] = LoadTexture("assets/yellowbird-midflap.png");
  birdSprite[2] = LoadTexture("assets/yellowbird-downflap.png");
  pipeSprite = LoadTexture("assets/pipe-green.png");

  player.height = birdSprite[0].height;
  player.width = birdSprite[0].width;

  PIPE_H = pipeSprite.height;
  PIPE_W = pipeSprite.width;
  PIPE_GAP = player.height + 4.5;

  dieSound = LoadSound("assets/audio/die.wav");
  wingSound = LoadSound("assets/audio/wing.wav");
  pointSound = LoadSound("assets/audio/point.wav");
}

void MainGameState::handleInput() {
  if (IsKeyPressed(KEY_SPACE)) {
    player.vy = -300;
    PlaySound(wingSound);
  }
}

void MainGameState::update(float deltaTime) {
  player.vy += gravedad * deltaTime;
  player.y += player.vy * deltaTime;

  Rectangle playerRec = {player.x, player.y, player.width, player.height};

  spawnTimer += deltaTime;
  if (spawnTimer >= spawnEvery) {
    spawnTimer = 0.0f;

    int pipe_y_offset_top = GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2);
    float x = GetScreenWidth();

    float y_top = -pipe_y_offset_top;
    float y_bot = (PIPE_H - pipe_y_offset_top) +
                  GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2);

    Rectangle top{x, y_top, PIPE_W, PIPE_H}, bot{x, y_bot, PIPE_W, PIPE_H};
    PipePair pipe_pair{top, bot};

    pipes.emplace_back(pipe_pair);
  }

  for (auto &pipe : pipes) {
    if (CheckCollisionRecs(pipe.top, playerRec) ||
        CheckCollisionRecs(pipe.bot, playerRec) ||
        player.y > GetScreenHeight() || player.y < 0) {
      PlaySound(dieSound);
      this->state_machine->add_state(
          std::make_unique<GameOverState>(playerPoints), true);
    }

    pipe.top.x -= PIPE_SPEED * deltaTime * difficulty;
    pipe.bot.x -= PIPE_SPEED * deltaTime * difficulty;
  }

  if (!pipes.empty() && pipes.front().bot.x < 0)
    pipes.pop_front();

  for (auto &pipe : pipes) {
    if (!pipe.scored && (pipe.bot.x + pipe.bot.width) < player.x) {
      PlaySound(pointSound);
      playerPoints++;
      difficulty += 0.1;
      pipe.scored = true;
    }
  }
}

void MainGameState::render() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Bienvenido a Flappy Bird DCA", 40, GetScreenHeight() / 2, 15,
           DARKGRAY);

  static float birdAnimTimer = 0.0f;
  static int birdFrame = 0;
  birdAnimTimer += GetFrameTime();
  if (birdAnimTimer >= 0.15f) {
    birdAnimTimer = 0.0f;
    if (birdFrame == 2)
      birdFrame = 0;
    else
      birdFrame++;
  }
  DrawTexture(birdSprite[birdFrame], player.x, player.y, WHITE);

  for (auto &pipe : pipes) {
    DrawTextureEx(this->pipeSprite, {pipe.top.x + PIPE_W, pipe.top.y + PIPE_H},
                  180.f, 1.0f, WHITE);
    DrawTextureEx(this->pipeSprite, {pipe.bot.x, pipe.bot.y}, 0.f, 1.0f, WHITE);
  }

  DrawText(("Puntuación: " + std::to_string(playerPoints)).c_str(), 20, 20, 15,
           BLACK);

  EndDrawing();
}