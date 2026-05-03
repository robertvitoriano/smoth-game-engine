#pragma once
#include <chrono>
#include <memory>
namespace eng {

class Application;
class Engine {
 public:
  bool init();
  void run();
  void destroy();
  void setApplication(Application* app);
  Application* getApplication();

 private:
  std::unique_ptr<Application> m_application;
  std::chrono::steady_clock::time_point m_lastTimePoint;
};
}  // namespace eng
