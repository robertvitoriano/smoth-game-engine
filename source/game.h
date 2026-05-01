#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "constants.h"
#include "structures.h"

enum class Direction { Up, Down, Left, Right, None };

class Game {
 public:
  Game() = default;

  void SetRenderer(GLuint shaderProgram, GLuint vao, GLuint vbo,
                   GLuint uOffsetLoc, GLuint uScaleLoc, GLuint uColorLoc);
  void InitGame();
  void UpdateGame(float deltaTime);
  void RenderGame(GLFWwindow* window);
  void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                   int mods);

 private:
  int score = 0;
  bool gameOver = false;
  bool gameStarted = false;
  float timeSinceLastUpdate = 0.0f;
  float snakeSpeed = UPDATE_INTERVAL;

  Direction snakeDir = Direction::None;
  std::vector<Vec2i> snake = {Vec2i(5, 10), Vec2i(4, 10), Vec2i(3, 10)};
  Vec2i fruit;

  GLuint shaderProgram = 0;
  GLuint VAO = 0;
  GLuint VBO = 0;
  GLuint uOffsetLoc = 0;
  GLuint uScaleLoc = 0;
  GLuint uColorLoc = 0;

  void SpawnFruit();
  void ResetGame();
  void DrawCell(const Vec2i& position, const Vec3& color);
  void DrawChar(char c, float x, float y, float scale, const Vec3& color);
  void DrawText(const std::string& text, float x, float y, float scale,
                const Vec3& color);
  void DrawBorder();
  void DrawSnake();
  void DrawScore();
  void DrawGameOver();
  void DrawStartScreen();
};

#endif
