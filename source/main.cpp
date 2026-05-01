#include <stdio.h>
#include <GLFW/glfw3.h>

int main()
{
#if defined(__linux__)
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
  printf("Hello, world!\n");
  return 0;
}
