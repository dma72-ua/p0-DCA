#include "MainGameState.hpp"
#include "GameOverState.hpp"
#include "StateMachine.hpp"
#include <iostream>
#include <string>

MainGameState::MainGameState() {
  player.x = 200;
  player.y = 200;
  gravedad = 400;
  playerPoints = 0;
}

void MainGameState::init() {}

void MainGameState::handleInput() {
  if (IsKeyPressed(KEY_SPACE))
    player.vy = -300;
}

void MainGameState::update(float deltaTime) {
  player.vy += gravedad * deltaTime;
  player.y += player.vy * deltaTime;

  Rectangle playerRec = {static_cast<float>(player.x - 17.0),
                         static_cast<float>(player.y - 17.0), 17.0, 17.0};

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
        CheckCollisionRecs(pipe.bot, playerRec)) {
      this->state_machine->add_state(
          std::make_unique<GameOverState>(playerPoints), true);
    }

    pipe.top.x -= PIPE_SPEED * deltaTime;
    pipe.bot.x -= PIPE_SPEED * deltaTime;
  }

  if (!pipes.empty() && pipes.front().bot.x < 0)
    pipes.pop_front();

  for (auto &pipe : pipes) {
    if (!pipe.scored && (pipe.bot.x + pipe.bot.width) < player.x) {
      playerPoints++;
      pipe.scored = true;
    }
  }
}

void MainGameState::render() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Bienvenido a Flappy Bird DCA", 40, GetScreenHeight() / 2, 15,
           DARKGRAY);

  DrawCircle(player.x, player.y, 17.0, RED);

  for (auto &pipe : pipes) {
    DrawRectangleRec(pipe.top, GREEN);
    DrawRectangleRec(pipe.bot, GREEN);
  }

  DrawText(("Puntuación: " + std::to_string(playerPoints)).c_str(), 20, 20, 15,
           BLACK);

  EndDrawing();
}