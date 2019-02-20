#include "main.h"
#include "plane.h"

#ifndef COMBAT_H
#define COMBAT_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z);
    glm::vec3 position;
    float rotation;

    float radius;
    float length;
    float front;
    float back;

    bool fired;
    float speed_z;
    float speed_y;

    void draw(glm::mat4 VP);
    void tick(float yaw);
    void gravity(bool gravity_effect);
    void set_position(float x, float y, float z, float yaw);
    bounding_box_t bounding_box();
private:
    VAO *pointyend;    // How an object looks
    VAO *load;
    VAO *thrust;
};

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    // float fired;
    float speed_x;
    float speed_y;
    bool moveup;
    void draw(glm::mat4 VP);
    // void fire(Player Player);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *bomb;    // How an object looks
};
#endif // COMBAT_H