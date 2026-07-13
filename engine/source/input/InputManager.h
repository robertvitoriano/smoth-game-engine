#pragma once
#include <array>
namespace eng {
class InputManager {
 private:
  InputManager() = default;
  InputManager(const InputManager&) = delete;
  InputManager(InputManager&&) = delete;
  InputManager operator=(const InputManager&) = delete;
  InputManager& operator=(InputManager&&) = delete;

 public:
  void setKeyPressed(int key, bool pressed);
  bool isKeyPressed(int key);

 private:
  std::array<bool, 256> m_keys = {false};
  friend class Engine;
};
}  // namespace eng
