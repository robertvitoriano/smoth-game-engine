#pragma once

namespace eng {
class Application {
 public:
  virtual bool init() = 0;
  // delata time in seconds
  virtual bool update(float deltaTime) = 0;

  virtual bool destroy() = 0;

  void setNeedsToBeClosed(bool value);
  bool needsToBeClosed() const;

 private:
  bool m_needsToBeClosed = false;
};
}  // namespace eng
