#include "MainGameState.hpp"
#include <iostream>

MainGameState::MainGameState()
{
    player.x = 200;
    player.y = 200;
    gravedad = 400;
}

void MainGameState::init()
{

}

void MainGameState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE))
        player.vy = -300;
}

void MainGameState::update(float deltaTime)
{
    player.vy += gravedad * deltaTime;
    player.y += player.vy * deltaTime;
    // player.vy = 0;
}

void MainGameState::render()
{
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Bienvenido a Flappy Bird DCA", 20, 256, 15, BLACK);

            DrawCircle(player.x, player.y, 17.0, RED);

        EndDrawing();
}