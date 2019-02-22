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

class Shining {
public:
    Shining() {} //- By Stephen King xD
    Shining(float x, float z);
    glm::vec3 position;
    float radius;
    // float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
private:
    VAO *object;    // How an object looks 
};

class CheckpointIsland {
public:
    CheckpointIsland() {} 
    CheckpointIsland(float x, float z, float rotation);
    glm::vec3 position;
    float radius;
    float rotation;
    bool current;
    
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
private:
    VAO *island;    // How an object looks 
};

class CheckpointArrow {
public:
    CheckpointArrow() {}
    CheckpointArrow(float x, float y, float z);
    glm::vec3 position;
    float height;
    float arrowhead;
    float arrowwidth;
    float width;
    float equilibrium_y;

    bool moveup;
    float rotatespeed;
    float indicatespeed;

    void draw(glm::mat4 VP);
    void movement();
private:
    VAO* arrow;
};

class Cannons {
public:
    Cannons() {}
    Cannons(float x, float y, float z);
    glm::vec3 position;
    float height;
    float width;
    float innerradius;
    float outerradius;
    float spread;

    float yaw;
    float pitch;
    float rotatespeed;

    bool destroyed;
    void draw(glm::mat4 VP);
    void movement();
private:
    VAO* base;
    VAO* top; // top 
};
#endif // SEA_H