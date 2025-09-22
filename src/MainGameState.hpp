#pragma once
#include "GameState.hpp"
#include <deque>
#include <vector>

extern "C" {
#include "../vendor/include/raylib.h"
}

struct Bird {
  float x, y;
  float vy;
  float height, width;
};

struct PipePair {
  Rectangle top, bot;
  bool scored = false;
};

class MainGameState : public GameState {
public:
  MainGameState();
  ~MainGameState() = default;

  void init() override;
  void handleInput() override;
  void update(float deltaTime) override;
  void render() override;

  void pause() {};
  void resume() {};

private:
  char entered_key;
  Bird player;
  int playerPoints;
  int gravedad;

  std::deque<PipePair> pipes;

  float PIPE_W;
  float PIPE_H;

  float PIPE_GAP;
  float PIPE_SPEED = 120.0f;

  float spawnTimer = 0.0f;
  float spawnEvery = 1.6f;

  float difficulty = 1.0;

  std::vector<Texture2D> birdSprite;
  Texture2D pipeSprite;
  Texture2D backgroundSprite;

  Sound dieSound;
  Sound wingSound;
  Sound pointSound;
};