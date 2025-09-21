#include "GameOverState.hpp"
#include "MainGameState.hpp"
#include "StateMachine.hpp"
#include <iostream>

GameOverState::GameOverState() {}

void GameOverState::init() {}

void GameOverState::handleInput() {
  if (IsKeyPressed(KEY_SPACE))
    this->state_machine->add_state(std::make_unique<MainGameState>(), true);
}

void GameOverState::update(float deltaTime) {}

void GameOverState::render() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Game Over \npulsa espacio para \nvolver a jugar", 20, 256, 15,
           BLACK);

  EndDrawing();
}

void GameOverState::pause() {}
void GameOverState::resume() {}