#include "graphics/GraphicsAPI.h"

#include <iostream>

namespace eng {

std::shared_ptr<ShaderProgram> GraphicsAPI::createShaderProgram(
    const std::string& vertexSource, const std::string& fragmentSource) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderCString = vertexSource.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderCString, nullptr);
  glCompileShader(vertexShader);

  GLint success;

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "Error Vertex shader compilation failed: " << infoLog
              << std::endl;

    return nullptr;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderCstring = fragmentSource.c_str();
  glShaderSource(fragmentShader, 1, &fragmentShaderCstring, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

    std::cerr << "ERROR: Fragment_shader_compilation_failed" << infoLog
              << std::endl;
    return nullptr;
  }
  // APARTIR DAQUI
  //  ### CREATE SHADER PROGRAM AND link FRAGMENT AND VERTEX SHADERS ####
  GLuint shaderProgramId = glCreateProgram();

  glAttachShader(shaderProgramId, vertexShader);
  glAttachShader(shaderProgramId, fragmentShader);
  glLinkProgram(shaderProgramId);

  glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
    std::cerr << "ERROR: SHADER_PROGRAM_LINKING_FAILED";
    return nullptr;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return std::make_shared<ShaderProgram>(shaderProgramId);
}
void GraphicsAPI::bindShaderProgram(ShaderProgram* shaderProgram) {
  shaderProgram->bind();
}
}  // namespace eng
