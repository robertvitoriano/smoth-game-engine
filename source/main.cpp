#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
#if defined(__linux__)
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif

  if (!glfwInit())
  {
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(1280, 780, "SmothGameEngine", nullptr, nullptr);

  if (window == nullptr)
  {
    std::cout << "Error creating Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetWindowPos(window, 0, 150);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Hello, world!\n");
  return 0;
}
