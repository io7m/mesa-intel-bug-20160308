#define GL_GLEXT_PROTOTYPES 1
#include <assert.h>
#include <GL/glcorearb.h>
#include "example.h"
#include <stdio.h>
#include <string.h>

static GLuint vbo;
static GLuint vao;
static GLuint fbo;
static GLuint texture;

static void
check_error()
{
  int e = glGetError();
  assert (e == GL_NO_ERROR);
}

static const char *vs_source = "#version 330 core\n in vec4 position;\n void main() {\n gl_Position = position; }";
static const char *fs_source = "#version 330 core\n out vec2 o_color; void main() { o_color = vec2 (1.0, 1.0); }";

static const GLenum draw_buffers[] = {
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_NONE
};

void
example_init()
{
  glGenVertexArrays(1, &vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 4 * 4, (void *) 0L, GL_STATIC_DRAW);

  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  const int vs = glCreateShader(GL_VERTEX_SHADER);
  const int vs_length = strlen(vs_source);
  glShaderSource(vs, 1,  (const char **) &vs_source, &vs_length);
  glCompileShader(vs);

  const int fs = glCreateShader(GL_FRAGMENT_SHADER);
  const int fs_length = strlen(fs_source);
  glShaderSource(fs, 1,  (const char **) &fs_source, &fs_length);
  glCompileShader(fs);

  const int program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glUseProgram(program);

  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 640, 480, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
  glDrawBuffers(8, draw_buffers);
  assert (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

  check_error();
}

void
example_render()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
  glBindVertexArray(vao);
  glDrawArrays(GL_POINTS, 0, 1);
}

