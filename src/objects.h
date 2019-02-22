#include "main.h"
#include "plane.h"

#ifndef OBJECT_H
#define OBJECT_H

class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z);
    glm::vec3 position;
    float outerradius;
    float innerradius;
    float width;
    float rotation;
    bool collected;
    // bool reversetunnel(Player Player);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
    VAO *object2;
};

class Volcano {
public:
    Volcano() {}
    Volcano(float x, float z, float orientation);
    glm::vec3 position;
    float radius;
    float rotation;
    float tipradius;
    float height;
    float islandheight; 
    // bool collected;
    // bool reversetunnel(Player Player);
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *island;
    VAO *mountain;    // How an object looks 
    VAO *lava;
};

class Fueltank {
public:
    Fueltank() {}
    Fueltank(float x, float y, float z);
    glm::vec3 position;
    float outerradius;
    float innerradius;
    float width;
    float rotation;
    bool collected;
    // bool reversetunnel(Player Player);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;

    // float rotation;
    float radius;
    float innerradius;
    float outerradius;
    float width;

    float speed;
    bool moveup;
    bool destroyed;
    void draw(glm::mat4 VP);
    void movement();
    // bool detect_collision(Player Player);
    bounding_box_t bounding_box();
private:
    VAO *balloon;    // How an object looks
    VAO *string;
};

#endif // OBJECTS_H