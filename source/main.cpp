#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>

#include "game.h"
#include "shaders.h"

static void KeyCallbackBridge(GLFWwindow* window, int key, int scancode,
                              int action, int mods) {
  auto* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
  if (game) {
    game->KeyCallback(window, key, scancode, action, mods);
  }
}

int main() {
#if defined(__linux__)
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
  if (!glfwInit()) {
    std::cout << "Error initialising GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window =
      glfwCreateWindow(800, 800, "SnakeGame", nullptr, nullptr);
  if (!window) {
    std::cout << "Error creating window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    std::cout << "Error initialising GLEW" << std::endl;
    glfwTerminate();
    return -1;
  }

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderCStr = vertexShaderSource.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderCStr, NULL);
  glCompileShader(vertexShader);

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR:VERTEX_SHADER_COMPILATION_FAILED: " << infoLog
              << std::endl;
    glfwTerminate();
    return -1;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog
              << std::endl;
    glfwTerminate();
    return -1;
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FAILED: " << infoLog
              << std::endl;
    glfwTerminate();
    return -1;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLuint uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
  GLuint uScaleLoc = glGetUniformLocation(shaderProgram, "uScale");
  GLuint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");

  const float vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};

  GLuint VAO = 0;
  GLuint VBO = 0;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Game game;
  game.SetRenderer(shaderProgram, VAO, VBO, uOffsetLoc, uScaleLoc, uColorLoc);
  game.InitGame();
  glfwSetWindowUserPointer(window, &game);
  glfwSetKeyCallback(window, KeyCallbackBridge);

  auto lastTime = std::chrono::high_resolution_clock::now();
  while (!glfwWindowShouldClose(window)) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime =
        std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;

    glfwPollEvents();

    game.UpdateGame(deltaTime);
    game.RenderGame(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
