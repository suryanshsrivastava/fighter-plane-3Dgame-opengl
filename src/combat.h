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
    void update(glm::vec3 a, glm::vec3 b, glm::vec3 c);
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

class Cannon_Missile {
public:
    Cannon_Missile() {}
    Cannon_Missile(float x, float y, float z, glm::vec3 d);
    glm::vec3 position;
    float height;
    float width;
    float innerradius;
    float outerradius;
    float spread;
    glm::vec3 d;

    float yaw;
    float pitch;
    float rotatespeed;

    void draw(glm::mat4 VP);
    void movement();
private:
    VAO* base;
    VAO* top; // top 
};
#endif // COMBAT_H