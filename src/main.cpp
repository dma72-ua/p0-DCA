#include "MainGameState.hpp"
#include "StateMachine.hpp"
#include <chrono>
#include <memory>

int main() {
  float delta_time = 0.0f;

  StateMachine state_machine = StateMachine();
  state_machine.add_state(std::make_unique<MainGameState>(), false);
  state_machine.handle_state_changes(delta_time);

  const int screenWidth = 288;
  const int screenHeight = 512;
  InitWindow(screenWidth, screenHeight, "Flappy Bird DCA");

  while (!state_machine.is_game_ending()) {
    delta_time = GetFrameTime();
    state_machine.handle_state_changes(delta_time);
    state_machine.getCurrentState()->handleInput();
    state_machine.getCurrentState()->update(delta_time);
    state_machine.getCurrentState()->render();
  }

  return 0;
}
