#pragma once
#include "GameState.hpp"
extern "C" {
    #include "raylib.h"
}

struct Bird
{
  int x, y;
  float vy;
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
};