#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x0, float y0, float z0, color_t color);
    glm::vec3 position;
    // float rotation;
    
    float radius;
    float length;
    float nose;
    float engine;

    float rise;
    float yaw;
    float pitch;
    float tilt;

    float fuelleft;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_rise();
    void gravity( bool gravity_effect );
    void tick_yaw( bool clockwise);
    void tick_forward();
    void tick_roll( bool right);
    double speed;
private:
    VAO *cockpit;
    VAO *body;
    VAO *fuel;
    VAO *fin; // :")
    VAO *tailfin;
};

#endif // PLANE_H
