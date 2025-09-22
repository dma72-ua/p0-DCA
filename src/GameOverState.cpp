#include "GameOverState.hpp"
#include "MainGameState.hpp"
#include "StateMachine.hpp"
#include <iostream>

GameOverState::GameOverState(int points) { playerPoints = points; }

void GameOverState::init() {
  gameOverSprite = LoadTexture("assets/gameover.png");
}

void GameOverState::handleInput() {
  if (IsKeyPressed(KEY_SPACE))
    this->state_machine->add_state(std::make_unique<MainGameState>(), true);
}

void GameOverState::update(float deltaTime) {}

void GameOverState::render() {
  BeginDrawing();

  ClearBackground(DARKGRAY);

  DrawText(("Puntuación Final: " + std::to_string(playerPoints)).c_str(), 20,
           200, 22, GREEN);

  DrawTexture(gameOverSprite, 20, 256, WHITE);

  DrawText("Pulsa espacio para \nvolver a jugar", 20, 320, 20, RED);

  EndDrawing();
}

void GameOverState::pause() {}
void GameOverState::resume() {}