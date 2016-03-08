#define GL_GLEXT_PROTOTYPES 1
#include <GL/glcorearb.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "example.h"

static void
error_callback(int error, const char* description)
{
  fprintf(stderr, "%d: %s\n", error, description);
}

int
main(void)
{
  GLFWwindow* window;

  if (!glfwInit()) {
    fprintf(stderr, "Unable to initialize\n");
    return -1;
  }

  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(640, 480, "GLFW", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Unable to create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  printf("GL_VERSION: %s\n", glGetString(GL_VERSION));

  example_init();

  while (!glfwWindowShouldClose(window)) {
    example_render();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
