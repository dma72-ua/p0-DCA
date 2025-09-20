#pragma once
#include "GameState.hpp"
#include <deque>

extern "C" {
    #include "raylib.h"
}

struct Bird
{
  int x, y;
  float vy;
};

struct PipePair
{
  Rectangle top, bot;
  bool scored = false;
};

class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Bird player;
        int gravedad;

        std::deque<PipePair> pipes;

        static constexpr int PIPE_W = 32;
        static constexpr int PIPE_H = 320;

        static constexpr int PIPE_GAP = 120;
        static constexpr float PIPE_SPEED = 120.0f;

        float spawnTimer = 0.0f;
        float spawnEvery = 1.6f;
};