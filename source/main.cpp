#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

struct Vec2 {
  float x = 0.0f;
  float y = 0.0f;
};

Vec2 offsetVec;

void keyCallback(GLFWwindow* window, int key, int scanCode, int action,
                 int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_UP:
        offsetVec.y++;
        break;
      case GLFW_KEY_DOWN:
        offsetVec.y--;
        break;
      case GLFW_KEY_LEFT:
        offsetVec.x--;
        break;
      case GLFW_KEY_RIGHT:
        offsetVec.x++;
        break;
      default:
        break;
    }
  }
}

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

  glfwSetKeyCallback(window, keyCallback);

  std::string vertexShaderProgram = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    
    uniform vec2 uOffset;
    
    out vec3 vColor;
    
    void main()
    {
      vColor = color;
      gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
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
    uniform vec4 uColor;
    
    void main(){
      fragColor = vec4(vColor,1.0) * uColor;
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

  // clang-format off
std::vector<float> vertices = {
  0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right vertice
  -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top left vertice
  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left vertice
   0.5f,-0.5f, 0.0f,  1.0f, 0.0f, 1.0f, // bottom right vertice
};
  // clang-format on

  // clang-format off
// indices for showing how we should draw our vertices
std::vector<unsigned int> indices = {
  0,1,2, // first triangle
  0,2,3  // second triangle
};
  // clang-format on

  // ############### CREATE BUFFERS FOR SENDING VERTICES TO GPU MEMORy
  // ################# Create and activate buffer
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // transfer vertices data from system memory to GPU Memory
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(float),
               vertices.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // CREATE EBO (ELement buffer object) FOR STORING INDICES TO INDICATE HOW WE
  // SHOULD DRAW

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indices.size() * sizeof(unsigned int),
               indices.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // CREATE AND BIND VERTEX ARRAY OBJECT (VAO)
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

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

  GLint uColorLocation = glGetUniformLocation(shaderProgram, "uColor");

  GLint uOffsetLocation = glGetUniformLocation(shaderProgram, "uOffset");

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw in back buffer
    glUseProgram(shaderProgram);

    glUniform4f(uColorLocation, 0.1f, 0.0f, 0.0f, 1.0f);

    glUniform2f(uOffsetLocation, offsetVec.x, offsetVec.y);

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap to front buffer
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Hello, world!\n");
  return 0;
}
