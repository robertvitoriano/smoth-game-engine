#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

int main() {
#if defined(__linux__)
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif

  if (!glfwInit()) {
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window =
      glfwCreateWindow(1280, 780, "SmothGameEngine", nullptr, nullptr);

  if (window == nullptr) {
    std::cout << "Error creating Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetWindowPos(window, 0, 150);
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    glfwTerminate();
    return -1;
  }

  std::string vertexShaderProgram = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    
    out vec3 vColor;
    
    void main()
    {
      vColor = color;
      gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
  )";
  // ### VERTEX SHADER ####

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderCString = vertexShaderProgram.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderCString, nullptr);
  glCompileShader(vertexShader);

  GLint success;

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "Error Vertex shader compilation failed: " << infoLog
              << std::endl;
  }
  // ### FRAGMENT SHADER ####
  std::string fragmentShaderSource = R"(
    #version 330 core
    
    out vec4 fragColor;
    in vec3 vColor;
    
    void main(){
      fragColor = vec4(vColor,1.0);
    }
      
  )";

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderCstring = fragmentShaderSource.c_str();
  glShaderSource(fragmentShader, 1, &fragmentShaderCstring, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

    std::cerr << "ERROR: Fragment_shader_compilation_failed" << infoLog
              << std::endl;
  }
  // ### CREATE SHADER PROGRAM AND link FRAGMENT AND VERTEX SHADERS ####
  GLuint shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "ERROR: SHADER_PROGRAM_LINKING_FAILED";
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  std::vector<float> vertices = {
      0.0f,  // top vertice coordinates
      0.5f,
      0.0f,
      1.0f,  // top vertice Color
      0.0f,
      0.0f,
      -0.5f,  // left vertice coordinates
      -0.5f,
      0.0f,
      0.0f,  // left vertice Color
      1.0f,
      0.0f,
      0.5f,  // right-bottom vertice coordinates
      -0.5f,
      0.0f,
      0.0f,  // right-bottom vertice Color
      0.0f,
      1.0f,
  };

  // ############### CREATE BUFFERS FOR SENDING VERTICES TO GPU
  // MEMORY################# Create and activate buffer
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // transfer vertices data from system memory to GPU Memory
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(float),
               vertices.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // CREATE AND BIND VERTEX ARRAY OBJECT (VAO)
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // length of  a single vertice data (coordinates + color)
  float stride = 6 * sizeof(float);

  void* verticesOffset = (void*)0;

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, verticesOffset);
  glEnableVertexAttribArray(0);

  void* colorOffset = (void*)(3 * sizeof(float));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, colorOffset);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw in back buffer
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // swap to front buffer
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Hello, world!\n");
  return 0;
}
