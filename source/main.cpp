#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
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

  std::vector<float> vertices = {
      0.0f,  // top vertice
      0.5f,
      0.0f,
      -0.5f,  // left vertice
      -0.5f,
      0.0f,
      0.5f,  // right vertice
      -0.5f,
      0.0f,
  };

  while (!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Hello, world!\n");
  return 0;
}
