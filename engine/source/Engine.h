#pragma once
#include <chrono>
#include <memory>
struct GLFWwindow;
namespace eng {

class Application;
class Engine {
 public:
  bool init(int width, int height);
  void run();
  void destroy();
  void setApplication(Application* app);
  Application* getApplication();

 private:
  std::unique_ptr<Application> m_application;
  std::chrono::steady_clock::time_point m_lastTimePoint;
  GLFWwindow* m_window = nullptr;
};
}  // namespace eng
