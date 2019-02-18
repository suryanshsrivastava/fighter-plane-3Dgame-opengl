#include "main.h"
#include "plane.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z, float speed, float fuel, float altitude);
    glm::vec3 position;

    float speed_indicator_rotation;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // DASHBOARD_H
