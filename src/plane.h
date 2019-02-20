#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x0, float y0, float z0, color_t color);
    glm::vec3 position;
    
    float radius;
    float length;
    float nose;
    float engine;

    float rise;
    float yaw;
    float pitch;
    float tilt;

    int fuelleft;

    float center[3];
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_rise(bool up);
    // void gravity( bool gravity_effect );
    void tick_yaw(bool clockwise);
    void tick_forward();
    void tick_roll(bool right);
    void tick_pitch(bool upwards);
    double speed;

    // void ();
    bool detect_collision(float planecenter[], float x, float y, float z, float radius);
private:
    VAO *cockpit;
    VAO *body;
    VAO *fuel;
    VAO *fin; // :")
    VAO *tailfin;
};

#endif // PLANE_H
