#include "main.h"

#ifndef SCORE_H
#define SCORE_H

class Line {
  public:
    Line() {}
    Line(float fx, float fy, float tx, float ty);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);

  private:
    VAO *object;
};

class Digit
{
  public:
    Digit() {}
    Digit(char c, float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

  private:
    Line lines[8];
};

#endif // SCORE_H