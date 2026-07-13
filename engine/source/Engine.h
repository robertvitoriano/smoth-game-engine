#pragma once
#include <chrono>
#include <memory>

#include "input/InputManager.h"
struct GLFWwindow;
namespace eng {

class Application;
class Engine {
 public:
  static Engine& getInstance();

 private:
  Engine() = default;
  Engine(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine operator=(const Engine&) = delete;
  Engine& operator=(Engine&&) = delete;

 public:
  bool init(int width, int height);
  void run();
  void destroy();
  void setApplication(Application* app);
  Application* getApplication();
  InputManager& getInputManager();

 private:
  std::unique_ptr<Application> m_application;
  std::chrono::steady_clock::time_point m_lastTimePoint;
  GLFWwindow* m_window = nullptr;
  InputManager m_inputManager;
};
}  // namespace eng
