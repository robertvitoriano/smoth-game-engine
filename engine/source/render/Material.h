#pragma once
#include <memory>
#include <unordered_map>

#include "graphics/ShaderProgram.h"
namespace eng {
class ShaderProgram;
class Material {
 public:
  void setShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram);
  void setParam(const std::string& name, float value);
  void bind();

 private:
  std::shared_ptr<ShaderProgram> m_shaderProgram;
  std::unordered_map<std::string, float> m_floatParams;
};
}  // namespace eng
