#include "Game.h"

#include <GLFW/glfw3.h>

#include <iostream>

bool Game::init() { return true; };
void Game::update(float deltaTime) {
  auto& input = eng::Engine::getInstance().getInputManager();

  if (input.isKeyPressed(GLFW_KEY_A)) {
    std::cout << "[A] Key is pressed" << std::endl;
  }
};
void Game::destroy() {

};
