#include "Game.h"

#include <GLFW/glfw3.h>

#include <iostream>

bool Game::init() {
  std::string vertexShaderProgram = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    
    uniform vec2 uOffset;
    
    out vec3 vColor;
    
    void main()
    {
      vColor = color;
      gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
    }
  )";

  std::string fragmentShaderSource = R"(
    #version 330 core
    
    out vec4 fragColor;
    in vec3 vColor;
    uniform vec4 uColor;
    
    void main(){
      fragColor = vec4(vColor,1.0) * uColor;
    }
      
  )";

  auto& graphicsAPI = eng::Engine::getInstance().getGraphicsAPI();
  auto shaderProgram = graphicsAPI.createShaderProgram(vertexShaderProgram,
                                                       fragmentShaderSource);
  m_material.setShaderProgram(shaderProgram);
  std::cout << "SHADER PROGRAM IS" << shaderProgram << std::endl;
  return true;
};
void Game::update(float deltaTime) {
  auto& input = eng::Engine::getInstance().getInputManager();

  if (input.isKeyPressed(GLFW_KEY_A)) {
    std::cout << "[A] Key is pressed" << std::endl;
  }
};
void Game::destroy() {

};
