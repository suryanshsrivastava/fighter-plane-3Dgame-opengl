#include "main.h"
#include "plane.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class SpeedDial {
public:
    SpeedDial() {}
    SpeedDial(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

class Speed {
public:
    Speed() {}
    Speed(float x, float y);
    glm::vec3 position;
    float speedrotate;
    void tick_speed(float speed);
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, color_t COLOR);
    float height;
    float width;

    glm::vec3 position;
    void tick_speed(float speed);
    void draw(glm::mat4 VP);
private:
    VAO *object;
};
#endif // DASHBOARD_H
