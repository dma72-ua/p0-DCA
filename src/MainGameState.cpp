#include "MainGameState.hpp"
#include <iostream>

MainGameState::MainGameState()
{
}

void MainGameState::init()
{

}

void MainGameState::handleInput()
{

}

void MainGameState::update(float deltaTime)
{

}

void MainGameState::render()
{
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Bienvenido a Flappy Bird DCA", 20, 256, 15, BLACK);

        EndDrawing();
}