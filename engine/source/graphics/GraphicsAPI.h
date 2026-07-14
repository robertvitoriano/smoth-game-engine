#pragma once
#include <GL/glew.h>

#include <memory>

#include "graphics/ShaderProgram.h"
#include "render/Material.h"
namespace eng {
class ShaderProgram;
class Material;
class GraphicsAPI {
 public:
  std::shared_ptr<ShaderProgram> createShaderProgram(
      const std::string& vertexSource, const std::string& fragmentSource);

  void bindShaderProgram(ShaderProgram* shaderProgram);
  void bindMaterial(Material* material);
};
}  // namespace eng
