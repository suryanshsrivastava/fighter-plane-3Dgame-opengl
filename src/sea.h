#include "main.h"
#include "plane.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y, float z, float width, float length, color_t color);
    glm::vec3 position;
    float width;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // SEA_H
