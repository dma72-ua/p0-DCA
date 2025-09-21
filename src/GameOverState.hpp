#pragma once
#include "GameState.hpp"

extern "C" {
#include "../vendor/include/raylib.h"
}

class GameOverState : public GameState {
public:
  GameOverState();
  ~GameOverState() = default;

  void init() override;
  void handleInput() override;
  void update(float deltaTime) override;
  void render() override;
  void pause() override;
  void resume() override;

private:
  char entered_key;
};