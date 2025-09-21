#include "GameOverState.hpp"
#include <iostream>

GameOverState::GameOverState()
{
}

void GameOverState::init()
{

}

void GameOverState::handleInput()
{
}

void GameOverState::update(float deltaTime)
{
}

void GameOverState::render()
{
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Game Over", 20, 256, 15, BLACK);

        EndDrawing();
}

void GameOverState::pause() {}
void GameOverState::resume() {}